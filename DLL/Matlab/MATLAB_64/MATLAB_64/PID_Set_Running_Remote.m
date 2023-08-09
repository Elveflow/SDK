function [error] = PID_Set_Running_Remote(Regulator_ID, Channel_1_to_4, Running)
 % Elveflow Library
 % PID Module
 % 
 % Set to run/pause the selected PID loop. Only works when using the remote 
 % measurement functions.
 
error=calllib('Elveflow64', 'PID_Set_Running_Remote' , Regulator_ID, Channel_1_to_4, Running);


end