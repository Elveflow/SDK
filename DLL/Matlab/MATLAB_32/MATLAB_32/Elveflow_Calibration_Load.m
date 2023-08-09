function [error] = Elveflow_Calibration_Load(Path, Calib_Array_out, len)
 % Elveflow Library
 % OB1-AF1 Device
 % 
 % Load the calibration file located at Path and returns the calibration 
 % parameters in the Calib_Array_out. len is the Calib_Array_out array length. 
 % The function asks the user to choose the path if Path is not valid, empty 
 % or not a path. The function indicate if the file was found.
 
error=calllib('Elveflow32', 'Elveflow_Calibration_Load' , Path, Calib_Array_out, len);


end