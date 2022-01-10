#tested with Python 3.5.1 (IDE Eclipse V4.5.2 + Pydev V5.0.0)
#add python_xx and python_xx/DLL to the project path

import sys
from _ast import Load
sys.path.append('D:/dev/SDK/DLL64/DLL64')#add the path of the library here
sys.path.append('D:/dev/SDK/Python_64')#add the path of the LoadElveflow.py

from ctypes import *

from array import array

from Elveflow64 import *


#
# Initialization of Sensor Reader ( ! ! ! REMEMBER TO USE .encode('ascii') ! ! ! )
#
Instr_ID=c_int32()
print("Instrument name and sensor types are hardcoded in the Python script")
#see User guide to determine sensor types and NIMAX to determine the instrument name 
error=F_S_R_Initialization('My_F_S_R'.encode('ascii'),2,0,10,0,byref(Instr_ID)) 
#all functions will return error code to help you to debug your code, for further information refer to User Guide
print('error:%d' % error)
print("MSR ID: %d" % Instr_ID.value)


#
#Main loop
#
    
repeat=True
while repeat:
    answer=input('What to do (get_sens or exit) : ')
    
        
    if answer=="get_sens":
        data_sens=c_double()
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel)#convert to int
        set_channel=c_int32(set_channel)#convert to c_int32
        error=F_S_R_Get_Sensor_data(Instr_ID.value,set_channel,byref(data_sens))
        print('Press or Flow ch', set_channel.value,': ',data_sens.value)
        
    
    if answer=='exit':
        repeat=False
    
    print( 'error :', error)
        

error=F_S_R_Destructor(Instr_ID.value)