function [error] = M_S_R_D_Get_Sens_Data(M_S_R_D_ID, Channel_1_to_4, Sens_Data)
 % Elveflow Library
 % MSRD Device
 % 
 % Read the sensor of the requested channel.s
 % Units: Flow sensor: µl/min
 % Pressure: mbar
 % 
 % NB: For Digital Flow Senor, If the connection is lost, MSRD will be reseted 
 % and the return value will be zero
 
error=calllib('Elveflow64', 'M_S_R_D_Get_Sens_Data' , M_S_R_D_ID, Channel_1_to_4, Sens_Data);


end