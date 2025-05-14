function [error] = OB1_Calib_Save(OB1_ID_in, Path)
 % Elveflow Library
 % OB1 Device
 % 
 % Saves the actual calibration to the desired path. The function prompts the 
 % user to choose a path if no path is specified.
 
error=calllib('Elveflow32', 'OB1_Calib_Save' , OB1_ID_in, Path);


end