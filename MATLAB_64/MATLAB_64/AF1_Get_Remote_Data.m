function [error] = AF1_Get_Remote_Data(AF1_ID, Reg_Data, Sens_Data)
 % Elveflow Library
 % AF1 Device
 % 
 % Read the sensor and regulator values of the device.
 % Warning: This Function only extracts data obtained in the remote 
 % measurement loop
 % Sensor unit : mbar if pressure sensor, µl/min if flow sensor
 % Regulator unit : mbars
 
error=calllib('Elveflow64', 'AF1_Get_Remote_Data' , AF1_ID, Reg_Data, Sens_Data);


end