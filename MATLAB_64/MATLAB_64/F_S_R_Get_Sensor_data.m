function [error] = F_S_R_Get_Sensor_data(F_S_Reader_ID_in, Channel_1_to_4, output)
 % Elveflow Library
 % Sensor Reader or Flow Reader Device
 % 
 % Get the data from the selected channel.
 
error=calllib('Elveflow64', 'F_S_R_Get_Sensor_data' , F_S_Reader_ID_in, Channel_1_to_4, output);


end