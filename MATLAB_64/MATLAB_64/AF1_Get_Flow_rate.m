function [error] = AF1_Get_Flow_rate(AF1_ID_in, Flow)
 % Elveflow Library
 % AF1 Device
 % 
 % Get the Flow rate from the flow sensor connected on the AF1
 
error=calllib('Elveflow64', 'AF1_Get_Flow_rate' , AF1_ID_in, Flow);


end