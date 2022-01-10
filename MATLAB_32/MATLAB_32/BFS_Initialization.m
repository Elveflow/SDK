function [error] = BFS_Initialization(Visa_COM, BFS_ID_out)
 % Elveflow Library
 % BFS Device
 % 
 % Initiate the BFS device using device com port (ASRLXXX::INSTR where XXX is 
 % the com port that could be found in windows device manager). It return the 
 % BFS ID (number >=0) to be used with other function 
 
error=calllib('Elveflow32', 'BFS_Initialization' , Visa_COM, BFS_ID_out);


end