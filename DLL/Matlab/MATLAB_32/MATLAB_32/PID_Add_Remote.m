function [error] = PID_Add_Remote(Regulator_ID, Regulator_Channel_1_to_4, ID_Sensor, Sensor_Channel_1_to_4, P, I, Running)
 % Elveflow Library
 % PID Module
 % 
 % Configure a PID loop between a regulator and a sensor. Only works when 
 % using the remote measurement functions.
 
error=calllib('Elveflow32', 'PID_Add_Remote' , Regulator_ID, Regulator_Channel_1_to_4, ID_Sensor, Sensor_Channel_1_to_4, P, I, Running);


end