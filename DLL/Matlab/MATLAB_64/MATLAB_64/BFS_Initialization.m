function [error] = BFS_Initialization(Visa_COM, Filter, M_temp, M_density, BFS_ID_out)
 % Elveflow Library
 % BFS Device
 % 
 % Initiate the BFS device using device com port (ASRLXXX::INSTR where XXX is 
 % the com port that could be found in windows device manager). It return the 
 % BFS ID (number >=0) to be used with other function 
 
error=calllib('Elveflow64', 'BFS_Initialization' , Visa_COM, Filter, M_temp, M_density, BFS_ID_out);


end