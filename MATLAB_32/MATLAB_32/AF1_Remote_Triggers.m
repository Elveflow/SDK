function [error] = AF1_Remote_Triggers(AF1_ID, TriggerIn, TriggerOut)
 % Elveflow Library
 % AF1 Device
 % 
 % Set the Trigger input and get the Trigger output of the AF1 device.
 
error=calllib('Elveflow32', 'AF1_Remote_Triggers' , AF1_ID, TriggerIn, TriggerOut);


end