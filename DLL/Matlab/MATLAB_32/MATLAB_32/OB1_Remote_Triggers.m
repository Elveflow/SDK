function [error] = OB1_Remote_Triggers(OB1_ID, TriggerIn, TriggerOut)
 % Elveflow Library
 % OB1 Device
 % 
 % Set the Trigger input and get the Trigger output of the OB1 device.
 
error=calllib('Elveflow32', 'OB1_Remote_Triggers' , OB1_ID, TriggerIn, TriggerOut);


end