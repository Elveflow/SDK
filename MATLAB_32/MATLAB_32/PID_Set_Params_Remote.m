function [error] = PID_Set_Params_Remote(Regulator_ID, Channel_1_to_4, Reset, P, I)
 % Elveflow Library
 % PID Module
 % 
 % Change the parameters of the selected PID loop. Only works when using the 
 % remote measurement functions.
 
error=calllib('Elveflow32', 'PID_Set_Params_Remote' , Regulator_ID, Channel_1_to_4, Reset, P, I);


end