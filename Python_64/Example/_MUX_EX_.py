#tested with Python 3.5.1 (IDE Eclipse V4.5.2 + Pydev V5.0.0)
#add python_xx and python_xx/DLL to the project path

import sys
sys.path.append('D:/dev/SDK/DLL64/DLL64')#add the path of the library here
sys.path.append('D:/dev/SDK/Python_64')#add the path of the LoadElveflow.py

from ctypes import *

from array import array

from Elveflow64 import *


#
# Initialization of MUX ( ! ! ! REMEMBER TO USE .encode('ascii') ! ! ! )
#
Instr_ID=c_int32()
print("Instrument name is hardcoded in the Python script")
#see User Guide and NIMAX to determine the instrument name 
error=MUX_Initialization('Dev4'.encode('ascii'),byref(Instr_ID)) 
#all functions will return error codes to help you to debug your code, for further information see User Guide
print('error:%d' % error)
print("MUX ID: %d" % Instr_ID.value)

#
#Main loop
#
    
repeat=True
while repeat:
    answer=input('what to do (set_all_valves_off, set_all_valves_on, set_all_valves_MUXWire, set_indiv_valve(MUX_QUAKE), get_trig, set_trig or exit) : ')
    if answer=='set_all_valves_off':
        valve_state=(c_int32*16)(0)
        for i in range (0 ,16):
            print ('[',i,']:',valve_state[i])
        error=MUX_Set_all_valves(Instr_ID.value, valve_state, 16)
    
    if answer=='set_all_valves_on':
        valve_state=(c_int32*16)(0)
        for i in range (0 ,16):
            valve_state[i]=c_int32(1)
        error=MUX_Set_all_valves(Instr_ID.value, valve_state, 16)   
        
    if answer=='set_all_valves_MUXWire':
        valve_state=(c_int32*16)(0)
        for i in range (0,16):
            valve_state[i]=c_int32(i%2)#set one valve on one valve off
        error=MUX_Wire_Set_all_valves(Instr_ID.value, valve_state, 16)
             

    if answer=="get_trig":
        trigger_ext=c_int32()  
        error=MUX_Get_Trig(Instr_ID, byref(trigger_ext))
        if trigger_ext.value==1:
            print('trigger high')
        else: 
            print('trigger low')
            
    if answer=="set_trig":
        trigger_int_val=input("set trigger value (high=1, low=0): ")
        trigger_int_val=int(trigger_int_val)#convert to int
        trigger_int_val=c_int32(trigger_int_val)#convert to c_int32
        error=MUX_Set_Trig(Instr_ID, trigger_int_val)

    if answer=='exit':
        repeat=False
    
    print( 'error :', error)
        

error=MUX_Destructor(Instr_ID.value)