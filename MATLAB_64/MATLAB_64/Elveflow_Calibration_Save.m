function [error] = Elveflow_Calibration_Save(Path, Calib_Array_in, len)
 % Elveflow Library
 % OB1-AF1 Device
 % 
 % Save the Calibration cluster in the file located at Path. len is the 
 % Calib_Array_in array length. The function prompt the user to choose the 
 % path if Path is not valid, empty or not a path.
 
error=calllib('Elveflow64', 'Elveflow_Calibration_Save' , Path, Calib_Array_in, len);


end