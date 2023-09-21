#tested with Python 3.5.1 (IDE Eclipse V4.5.2 + Pydev V5.0.0)
#add python_xx and python_xx/DLL to the project path

import sys
sys.path.append('C:/Users/David/Documents/ELVESYS/Python/SDK373debug/DLL32')#add the path of the library here
sys.path.append('C:/Users/David/Documents/ELVESYS/Python/SDK373debug')#add the path of the LoadElveflow.py

from ctypes import *

from array import array

from Elveflow32 import *


#
# Initialization of MUX ( ! ! ! REMEMBER TO USE .encode('ascii') ! ! ! )
#
Instr_ID=c_int32()
print("Instrument name is hardcoded in the Python script")
#see User Guide and NIMAX to determine the instrument name 
error=MUX_Initialization('COM6'.encode('ascii'),byref(Instr_ID)) 
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

    if answer=="set_type":
        valveNb_int_val=input("Choose the valve number (1 to 8) ")
        valveNb_int_val = int(valveNb_int_val)
        type_int_val=input("choose valve type you want ( 0 for Undefined,4 for NC, 5 for NO or 6 Universal) ")
        type_int_val = int(type_int_val)
        error=MUX_Set_valves_Type (Instr_ID.value, valveNb_int_val, type_int_val)

    if answer=="get_type":
        valveNb_int_val=input("Choose the valve number (1 to 8) ")
        valveNb_int_val = int(valveNb_int_val)
        Types_array=(c_int32*8)(0)
        MUX_Get_valves_Type (Instr_ID.value, Types_array, 8)
        print ('Valve type is :')
        print('[',valveNb_int_val,']: ',Types_array[valveNb_int_val-1])
        print ('valve type 0 (undifined); 1(NC); 2(NO); 3(Universal); 4 (NC Custom); 5 (NO Custom); 6(Universal Custom)')

    if answer=='exit':
        repeat=False
    
    print( 'error :', error)
        

error=MUX_Destructor(Instr_ID.value)