function [error] = AF1_Set_Press(AF1_ID_in, Pressure, Calib_array_in, len)
 % Elveflow Library
 % AF1 Device
 % 
 % Set the pressure of the AF1 device, Calibration array is required (use 
 % Set_Default_Calib if required).Len correspond to the Calib_array_in length.
 % 
 
error=calllib('Elveflow64', 'AF1_Set_Press' , AF1_ID_in, Pressure, Calib_array_in, len);


end