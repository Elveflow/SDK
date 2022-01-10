function [error] = AF1_Calib(AF1_ID_in, Calib_array_out, len)
 % Elveflow Library
 % AF1 Device
 % 
 % Launch AF1 calibration and return the calibration array. Len correspond to 
 % the Calib_array_out length.
 
error=calllib('Elveflow64', 'AF1_Calib' , AF1_ID_in, Calib_array_out, len);


end