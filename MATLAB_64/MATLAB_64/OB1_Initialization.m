function [error] = OB1_Initialization(Device_Name, Reg_Ch_1, Reg_Ch_2, Reg_Ch_3, Reg_Ch_4, OB1_ID_out)
 % Elveflow Library
 % OB1 Device
 % 
 % Initialize the OB1 device using device name and regulators type (see SDK 
 % Z_regulator_type for corresponding numbers). It modify the OB1 ID (number 
 % >=0). This ID can be used be used with other function to identify the 
 % targed OB1. If an error occurs during the initialization process, the OB1 
 % ID value will be -1. 
 
error=calllib('Elveflow64', 'OB1_Initialization' , Device_Name, Reg_Ch_1, Reg_Ch_2, Reg_Ch_3, Reg_Ch_4, OB1_ID_out);


end