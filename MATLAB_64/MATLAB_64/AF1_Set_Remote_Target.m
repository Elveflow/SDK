function [error] = AF1_Set_Remote_Target(AF1_ID, Target)
 % Elveflow Library
 % AF1 Device
 % 
 % Set the Target of the AF1 device. Modify the pressure if the PID is off, or 
 % the sensor is a pressure sensor. Modify a flow if the sensor is a flow 
 % sensor and the PID is on.
 
error=calllib('Elveflow64', 'AF1_Set_Remote_Target' , AF1_ID, Target);


end