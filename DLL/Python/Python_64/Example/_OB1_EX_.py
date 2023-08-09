#tested with Python 3.6.10 (IDE Notepad++ v8.5.4)
#add python_xx and python_xx/DLL to the project path
#coding: utf8

import sys
from email.header import UTF8
sys.path.append('D:/dev/SDK/DLL64/DLL64')#add the path of the library here
sys.path.append('D:/dev/SDK/Python_64')#add the path of the LoadElveflow.py

from ctypes import *

from array import array

from Elveflow64 import *


#
# Initialization of OB1 ( ! ! ! REMEMBER TO USE .encode('ascii') ! ! ! )
#
Instr_ID=c_int32()
print("Instrument name and regulator types are hardcoded in the Python script")
#see User Guide to determine regulator types and NIMAX to determine the instrument name 
error=OB1_Initialization('COM4'.encode('ascii'),0,0,0,0,byref(Instr_ID)) 
#all functions will return error codes to help you to debug your code, for further information refer to User Guide
print('error:%d' % error)
print("OB1 ID: %d" % Instr_ID.value)

#add one digital flow sensor with water calibration, all information to declare sensors are described in the User Guide
error=OB1_Add_Sens(Instr_ID, 1, 4, 1, 0, 7, 0)
#(CustomSens_Voltage_5_to_25 only works with CustomSensors and OB1 from 2020 and after)
print('error add digit flow sensor:%d' % error)


#add one analog flow sensor
#error=OB1_Add_Sens(Instr_ID, 1, 5, 0, 0, 7, 0)
#(CustomSens_Voltage_5_to_25 only works with CustomSensors and OB1 from 2020 and after)
#print('error add analog flow sensor:%d' % error)



#
#Set the calibration type
#

Calib=(c_double*1000)()#always define array this way, calibration should have 1000 elements
repeat=True
while repeat==True:
    answer=input('select calibration type (default, load, new ) : ')
    #answer='default'#test purpose only
    Calib_path='C:\\Users\\Public\\Desktop\\Calibration\\Calib.txt'
    if answer=='default':
        error=Elveflow_Calibration_Default (byref(Calib),1000)
        #for i in range (0,1000):
            #print('[',i,']: ',Calib[i])
        repeat=False
    if answer=='load':
        error=Elveflow_Calibration_Load (Calib_path.encode('ascii'), byref(Calib), 1000)
        #for i in range (0,1000):
            #print('[',i,']: ',Calib[i])
        repeat=False
        
    if answer=='new':
        OB1_Calib (Instr_ID.value, Calib, 1000)
        #for i in range (0,1000):
            #print('[',i,']: ',Calib[i])
        error=Elveflow_Calibration_Save(Calib_path.encode('ascii'), byref(Calib), 1000)
        print ('calib saved in %s' % Calib_path.encode('ascii'))
        repeat=False


#
#Main loop
#
    
repeat=True
while repeat:
    answer=input('what to do (set_p, get_p, get_sens, get_all, get_trig, set_trig, add_pid, start, stop, set_target, read_channel, or exit) : ')
    if answer=='set_p':
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel)#convert to int
        set_channel=c_int32(set_channel)#convert to c_int32
        set_pressure=input("select pressure (-1000 to 8000 mbars) : ")
        set_pressure=float(set_pressure) 
        set_pressure=c_double(set_pressure)#convert to c_double
        error=OB1_Set_Press(Instr_ID.value, set_channel, set_pressure, byref(Calib),1000) 
        
        
    if answer=='get_p':
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel)#convert to int
        set_channel=c_int32(set_channel)#convert to c_int32
        get_pressure=c_double()
        error=OB1_Get_Press(Instr_ID.value, set_channel, 1, byref(Calib),byref(get_pressure), 1000)#Acquire_data=1 -> read all the analog values
        print('error: ', error)
        print('ch',set_channel.value,': ',get_pressure.value)
        #print('ch1: ', get_pressure()[0] , ' mbar\nch2: ', get_pressure()[1] ,' mbar\nch3: ', get_pressure()[2] , ' mbar\nch4: ', get_pressure()[3] ,' mbar')
        
    if answer=="get_all":
        data_sens=c_double()
        get_pressure=c_double()
        error=OB1_Get_Press(Instr_ID.value, 1, 1, byref(Calib),byref(get_pressure), 1000)#Ch=1;  Acquire_data=1 -> read all the analog values
        print('error: ', error)
        print('Press ch 1: ',get_pressure.value)
        
        for i in range(2,5):
            error=OB1_Get_Press(Instr_ID.value, i, 0, byref(Calib),byref(get_pressure), 1000)#Ch=i;  Acquire_data=0 -> use the values acquired in OB1_Get_Press
            print('error: ', error)
            print('Press ch ', i,': ',get_pressure.value) 
       
        for i in range(1,5):
            error=OB1_Get_Sens_Data(Instr_ID.value, i, 0, byref(data_sens))#Ch=i;  Acquire_data=0 -> use the values acquired in OB1_Get_Press
            print('error: ', error)
            print('Sens ch ', i,': ',data_sens.value) 
       
    if answer=="get_sens":
        data_sens=c_double()
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel)#convert to int
        set_channel=c_int32(set_channel)#convert to c_int32
        error=OB1_Get_Sens_Data(Instr_ID.value,set_channel, 1,byref(data_sens))#Acquire_data=1 -> read all the analog values
        print('Press or Flow ch', set_channel.value,': ',data_sens.value)
        
    if answer=="get_trig":
        trigger_ext=c_int32()  
        error=OB1_Get_Trig(Instr_ID, byref(trigger_ext))
        if trigger_ext.value==1:
            print('trigger high')
        else: 
            print('trigger low')
            
    if answer=="set_trig":
        trigger_int_val=input("set trigger value (high=1, low=0): ")
        trigger_int_val=int(trigger_int_val)#convert to int
        trigger_int_val=c_int32(trigger_int_val)#convert to c_int32
        error=OB1_Set_Trig(Instr_ID, trigger_int_val)

    if answer=='add_pid':
        set_channel_regulator=input("select channel regulator (1-4) : ")
        set_channel_regulator=int(set_channel_regulator)#convert to int
        set_channel_regulator=c_int32(set_channel_regulator)#convert to c_int32
        set_channel_sensor=input("select channel sensor (1-4) : ")
        set_channel_sensor=int(set_channel_sensor)#convert to int
        set_channel_sensor=c_int32(set_channel_sensor)#convert to c_int32
        error=PID_Add_Remote(Instr_ID.value, set_channel_regulator, Instr_ID.value, set_channel_sensor,10,0.1,1) 

    if answer=="start":
        error=OB1_Start_Remote_Measurement(Instr_ID.value, byref(Calib), 1000)
    
    if answer=="stop":
        error=OB1_Stop_Remote_Measurement(Instr_ID.value)
            
    if answer=="read_channel":
        data_sens=c_double()
        data_reg=c_double()
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel)#convert to int
        set_channel=c_int32(set_channel)#convert to c_int32
        error=OB1_Get_Remote_Data(Instr_ID.value,set_channel, byref(data_reg),byref(data_sens))
        print('Regulator/Sensors: ', data_reg.value,'; ',data_sens.value)

    if answer=='set_target':
        set_channel=input("select channel(1-4) : ")
        set_channel=int(set_channel)#convert to int
        set_channel=c_int32(set_channel)#convert to c_int32
        set_target=input("select pressure (-1000 to 8000 mbars) : ")
        set_target=float(set_target) 
        set_target=c_double(set_target)#convert to c_double
        error=OB1_Set_Remote_Target(Instr_ID.value, set_channel, set_target) 

    if answer=='exit':
        repeat=False
    
    print( 'error :', error)
        
#UPDATE
#stop measurement

error=OB1_Destructor(Instr_ID.value)