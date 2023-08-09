function [error] = BFS_Get_Temperature(BFS_ID_in, Temperature)
 % Elveflow Library
 % BFS Device
 % 
 % Get the fluid temperature (in °C) of the BFS defined by the BFS_ID
 
error=calllib('Elveflow64', 'BFS_Get_Temperature' , BFS_ID_in, Temperature);


end