function [error] = AF1_Set_Trig(AF1_ID_in, trigger)
 % Elveflow Library
 % AF1 Device
 % 
 % Set the Trigger of the AF1 device (0=0V, 1=5V).
 
error=calllib('Elveflow32', 'AF1_Set_Trig' , AF1_ID_in, trigger);


end