function [error] = F_S_R_Initialization(Device_Name, Sens_Ch_1, Sens_Ch_2, Sens_Ch_3, Sens_Ch_4, F_S_Reader_ID_out)
 % Elveflow Library
 % Sensor Reader or Flow Reader Device
 % 
 % Initiate the F_S_R device using device name (could be obtained in NI MAX) 
 % and sensors. It return the F_S_R ID (number >=0) to be used with other 
 % function. 
 % NB: Flow reader can only accept Flow sensor
 % NB 2: Sensor connected to channel 1-2 and 3-4 should be the same type 
 % otherwise they will not be taken into account and the user will be informed 
 % by a prompt message.
 
error=calllib('Elveflow32', 'F_S_R_Initialization' , Device_Name, Sens_Ch_1, Sens_Ch_2, Sens_Ch_3, Sens_Ch_4, F_S_Reader_ID_out);


end