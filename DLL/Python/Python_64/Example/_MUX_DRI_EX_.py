#tested with Python 3.5.1 (IDE Microsoft Visual Studio 2019)
#add python_xx and python_xx/DLL to the project path

import sys
sys.path.append('D:/dev/SDK/DLL64/DLL64')#add the path of the library here
sys.path.append('D:/dev/SDK/Python_64')#add the path of the LoadElveflow.py

from ctypes import *

from array import array

from Elveflow64 import *


#
# Initialization of MUX Distribution, Distributor, Recirculation or Injection ( ! ! ! REMEMBER TO USE .encode('ascii') ! ! ! )
#
Instr_ID=c_int32()
print("Instrument name is hardcoded in the Python script")
#see User Guide and NIMAX to determine the instrument name 
error=MUX_DRI_Initialization("ASRL4::INSTR".encode('ascii'),byref(Instr_ID))#choose the COM port, it can be ASRLXXX::INSTR (where XXX=port number)
#all functions will return error codes to help you to debug your code, for further information see User Guide
print('error:%d' % error)
print("MUX DRI ID: %d" % Instr_ID.value)

#define the Answer (when asking serial number...), 40 elements is enough for the Answer
Answer=(c_char*40)()

#
#Main loop
#
    
repeat=True
while repeat:
    answer=input('what to do (get_valve, set_valve, home_valve, get_serial_number or exit) : ')
    
        
    if answer=="get_valve":
        valve=c_int32(-1)
        error=MUX_DRI_Get_Valve(Instr_ID.value,byref(valve)) #get the active valve. it returns 0 if valve is busy.
        print('selected channel',valve.value)
        
    if answer=="set_valve":
        valve2=c_double()
        Valve2=input("select valve (1-6, 1-10, 1-12, 1/2) : ") #refer to SDK User Guide for valve selection depending on your instrument
        Valve2=int(Valve2)#convert to int
        Valve2=c_int32(Valve2)#convert to c_int32
        error=MUX_DRI_Set_Valve(Instr_ID.value,Valve2,0) #you can select valve rotation way, either shortest, clockwise or counter clockwise (only for MUX Distribution and Recirculation)

    if answer=="home_valve":
        #send the command to Home the valve (only for MUX Distribution and Recirculation)
        #Home the valve can take several seconds. Wait for the end of the valve movement to be able to set a new valve position.
        error=MUX_DRI_Send_Command(Instr_ID.value,0,Answer,40) #length is set to 40 to contain the whole Serial Number
        print('Answer',Answer.value)

    if answer=="get_serial_number":
        #send the command to get the Serial Number (only for MUX Distribution and Recirculation)
        error=MUX_DRI_Send_Command(Instr_ID.value,1,Answer,40) #length is set to 40 to contain the whole Serial Number
        print('Answer',Answer.value)
            
    if answer=='exit':
        repeat=False
    
    print( 'error :', error)
        

error=MUX_DRI_Destructor(Instr_ID.value)