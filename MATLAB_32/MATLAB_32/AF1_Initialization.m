function [error] = AF1_Initialization(Device_Name, Pressure_Regulator, Sensor, AF1_ID_out)
 % Elveflow Library
 % AF1 Device
 % 
 % IInitiate the AF1 device using device name (could be obtained in NI MAX), 
 % and regulator, and sensor. It return the AF1 ID (number >=0) to be used 
 % with other function 
 
error=calllib('Elveflow32', 'AF1_Initialization' , Device_Name, Pressure_Regulator, Sensor, AF1_ID_out);


end