function [error] = MUX_Initialization(Device_Name, MUX_ID_out)
 % Elveflow Library
 % Mux Device
 % 
 % Initiate the MUX device using device name (could be obtained in NI MAX). It 
 % return the F_S_R ID (number >=0) to be used with other function
 
error=calllib('Elveflow64', 'MUX_Initialization' , Device_Name, MUX_ID_out);


end