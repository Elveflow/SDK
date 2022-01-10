function [error] = AF1_Get_Press(AF1_ID_in, Integration_time, Calib_array_in, Pressure, longueur)
 % Elveflow Library
 % AF1 Device
 % 
 % Get the pressure of the AF1 device, Calibration array is required (use 
 % Set_Default_Calib if required). Len correspond to the Calib_array_in 
 % length.
 
error=calllib('Elveflow32', 'AF1_Get_Press' , AF1_ID_in, Integration_time, Calib_array_in, Pressure, longueur);


end