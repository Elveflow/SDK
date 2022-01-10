function [error] = OB1_Stop_Remote_Measurement(OB1_ID)
 % Elveflow Library
 % OB1 Device
 % 
 % Stop the background measure & control loop
 
error=calllib('Elveflow32', 'OB1_Stop_Remote_Measurement' , OB1_ID);


end