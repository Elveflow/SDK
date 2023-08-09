function [error] = M_S_R_D_Initialization(Device_Name, Sens_Ch_1, Sens_Ch_2, Sens_Ch_3, Sens_Ch_4, CustomSens_Voltage_Ch12, CustomSens_Voltage_Ch34, MSRD_ID_out)
 % Elveflow Library
 % MSRD Device
 % 
 % Initialize the Sensor Reader device able to read digital sensors (MSRD) 
 % using device name and sensors type (see SDK Z_sensor_type for corresponding 
 % numbers). It modify the MSRD ID (number >=0). This ID can be used with 
 % other function to identify the targeted MSRD. If an error occurs during the 
 % initialization process, the MSRD ID value will be -1. 
 % 
 % Initiate the communication with the Sensor Reader able to read digital 
 % sensors (MSRD). This VI generates an identification cluster of the 
 % instrument to be used with other VIs.
 % 
 % NB: Sensor type has to be written here in addition to the "Add_Sens".
 % NB 2: Sensor connected to channel 1-2 and 3-4 have to be the same type 
 % otherwise they will not be taken into account. 
 
error=calllib('Elveflow32', 'M_S_R_D_Initialization' , Device_Name, Sens_Ch_1, Sens_Ch_2, Sens_Ch_3, Sens_Ch_4, CustomSens_Voltage_Ch12, CustomSens_Voltage_Ch34, MSRD_ID_out);


end