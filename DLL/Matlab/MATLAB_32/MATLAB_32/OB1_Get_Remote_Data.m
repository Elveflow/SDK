function [error] = OB1_Get_Remote_Data(OB1_ID, Channel_1_to_4, Reg_Data, Sens_Data)
 % Elveflow Library
 % OB1 Device
 % 
 % Read the sensor and regulator values of the requested channel.
 % Warning: This Function only extracts data obtained in the remote 
 % measurement loop
 % Sensor unit : mbar if pressure sensor, µl/min if flow sensor
 % Regulator unit : mbar
 % 
 % NB: For Digital Flow Senor, If the connection is lost, OB1 will be reseted 
 % and the return value will be zero
 
error=calllib('Elveflow32', 'OB1_Get_Remote_Data' , OB1_ID, Channel_1_to_4, Reg_Data, Sens_Data);


end