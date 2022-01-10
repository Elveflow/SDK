#tested with Python 3.5.1 (IDE Microsoft Visual Studio 2019)
#add python_xx and python_xx/DLL to the project path

import sys
from _ast import Load
sys.path.append('D:/dev/SDK/DLL64/DLL64')#add the path of the library here
sys.path.append('D:/dev/SDK/Python_64')#add the path of the LoadElveflow.py

from ctypes import *

from array import array

from Elveflow64 import *


#
#Initialization of MSRD ( ! ! ! REMEMBER TO USE .encode('ascii') ! ! ! )
#
Instr_ID=c_int32()
print("Instrument name and sensor types are hardcoded in the Python script")
#see User Guide to determine sensor types and NIMAX software to determine the instrument name (installed with ESI)
error=M_S_R_D_Initialization('01EE3A1A'.encode('ascii'),5,0,0,0,0,0,byref(Instr_ID)) 
#(CustomSens_Voltage_Ch12 and Ch34 is used for CustomSensors only, voltage is between 5 and 25V)
#all functions will return error code to help you to debug your code, for further information see User Guide
print('error:%d' % error)
print("MSRD ID: %d" % Instr_ID.value)

#add sensor
error=M_S_R_D_Add_Sens(Instr_ID, 1, 5, 0, 0, 7)#add digital flow sensor, if not found throw error 8000. remember that channel 1-2 or 3-4 should be of the same kind. sensor type should be the same as in the initialization step
print('error add digital flow sensor:%d' % error)

#set analog filter if needed
#ONOFF=c_bool(1)
#error=M_S_R_D_Set_Filt(Instr_ID,1,ONOFF) #set analog filter on channel 1

#
#Main loop
#
    
repeat=True
while repeat:
    answer=input('What to do (get_sens or exit) : ')
    
        
    if answer=="get_sens":
        data_sens=c_double()
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel) #convert to int
        set_channel=c_int32(set_channel) #convert to c_int32
        error=M_S_R_D_Get_Sens_Data(Instr_ID.value,set_channel,byref(data_sens))
        print('Press or Flow ch', set_channel.value,': ',data_sens.value)
        
    
    if answer=='exit':
        repeat=False
    
    print( 'error :', error)
        

error=M_S_R_D_Destructor(Instr_ID.value)