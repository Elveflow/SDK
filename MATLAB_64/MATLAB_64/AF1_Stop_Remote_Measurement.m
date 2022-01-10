function [error] = AF1_Stop_Remote_Measurement(AF1_ID)
 % Elveflow Library
 % AF1 Device
 % 
 % Stop the background measure & control loop
 
error=calllib('Elveflow64', 'AF1_Stop_Remote_Measurement' , AF1_ID);


end