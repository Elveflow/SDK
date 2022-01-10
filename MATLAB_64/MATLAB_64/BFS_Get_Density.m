function [error] = BFS_Get_Density(BFS_ID_in, Density)
 % Elveflow Library
 % BFS Device
 % 
 % Get fluid density (in g/L) for the BFS defined by the BFS_ID
 
error=calllib('Elveflow64', 'BFS_Get_Density' , BFS_ID_in, Density);


end