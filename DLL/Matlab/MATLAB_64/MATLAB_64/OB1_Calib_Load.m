function [error] = OB1_Calib_Load(OB1_ID_in, Path)
 % Elveflow Library
 % OB1 Device
 % 
 % Launch OB1 calibration and return the calibration array. Before 
 % Calibration, ensure that ALL channels are proprely closed with adequate 
 % caps. 
 % Len correspond to the Calib_array_out length.
 
error=calllib('Elveflow64', 'OB1_Calib_Load' , OB1_ID_in, Path);


end