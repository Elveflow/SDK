function [error] = OB1_Set_Remote_Target(OB1_ID, Channel_1_to_4, Target)
 % Elveflow Library
 % OB1 Device
 % 
 % Set the Target of the OB1 selected channel. Modify the pressure if the PID 
 % is off, or the sensor is a pressure sensor. Modify a flow if the sensor is 
 % a flow sensor and the PID is on.
 
error=calllib('Elveflow32', 'OB1_Set_Remote_Target' , OB1_ID, Channel_1_to_4, Target);


end