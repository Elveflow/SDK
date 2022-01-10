function [error] = OB1_Get_Sens_Data(OB1_ID, Channel_1_to_4, Acquire_Data1True0False, Sens_Data)
 % Elveflow Library
 % OB1 Device
 % 
 % Read the sensor of the requested channel. ! This Function only convert data 
 % that are acquired in OB1_Acquire_data
 % Units : Flow sensor µl/min
 % Pressure : mbar
 % 
 % If Acquire_data is true, the OB1 acquires ALL regulator AND ALL analog 
 % sensor value. They are stored in the computer memory. Therefore, if several 
 % regulator values (OB1_Get_Press) and/or sensor values (OB1_Get_Sens_Data) 
 % have to be acquired simultaneously, set the Acquire_Data to true only for 
 % the First function. All the other can used the values stored in memory and 
 % are almost instantaneous. For Digital Sensor, that required another 
 % communication protocol, this parameter have no impact
 % 
 % NB: For Digital Flow Senor, If the connection is lots, OB1 will be reseted 
 % and the return value will be zero
 
error=calllib('Elveflow64', 'OB1_Get_Sens_Data' , OB1_ID, Channel_1_to_4, Acquire_Data1True0False, Sens_Data);


end