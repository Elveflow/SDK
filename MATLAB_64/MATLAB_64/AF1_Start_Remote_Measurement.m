function [error] = AF1_Start_Remote_Measurement(AF1_ID, Calib_array_in, len)
 % Elveflow Library
 % AF1 Device
 % 
 % Start a loop running in the background, and automatically reads all sensors 
 % and regulators. No direct call to the AF1 can be made until the Stop 
 % measuring function is called. Until then only functions accessing this loop 
 % (get_remote_data, set_remote_target, remote_triggers) are recommended.
 
error=calllib('Elveflow64', 'AF1_Start_Remote_Measurement' , AF1_ID, Calib_array_in, len);


end