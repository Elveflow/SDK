function [error] = OB1_Get_All_Data(OB1_ID, PressureChannel1, SensorChannel1, PressureChannel2, SensorChannel2, PressureChannel3, SensorChannel3, PressureChannel4, SensorChannel4)
 % Elveflow Library
 % OB1 Device
 % 
 % Returns all the pressure and sensor measurements on all 4 channels of the 
 % OB1 device
 
error=calllib('Elveflow32', 'OB1_Get_All_Data' , OB1_ID, PressureChannel1, SensorChannel1, PressureChannel2, SensorChannel2, PressureChannel3, SensorChannel3, PressureChannel4, SensorChannel4);


end