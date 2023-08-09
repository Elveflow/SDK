function [error] = BFS_Destructor(BFS_ID_in)
 % Elveflow Library
 % BFS Device
 % 
 % Close Communication with BFS device
 
error=calllib('Elveflow32', 'BFS_Destructor' , BFS_ID_in);


end