function [error] = Elveflow_Calibration_Default(Calib_Array_out, len)
 % Elveflow Library
 % OB1-AF1 Device
 % 
 % Set default Calib in Calib cluster, len is the Calib_Array_out array length
 
error=calllib('Elveflow64', 'Elveflow_Calibration_Default' , Calib_Array_out, len);


end