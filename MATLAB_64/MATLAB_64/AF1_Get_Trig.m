function [error] = AF1_Get_Trig(AF1_ID_in, trigger)
 % Elveflow Library
 % AF1 Device
 % 
 % Get the trigger of the AF1 device (0=0V, 1=5V).
 % 
 
error=calllib('Elveflow64', 'AF1_Get_Trig' , AF1_ID_in, trigger);


end