function [error] = BFS_Get_Mass_Flow(BFS_ID_in, MassFlow)
 % Elveflow Library
 % BFS Device
 % 
 % Get the fluid mass flow in (g/h) of the BFS defined by the BFS_ID
 
error=calllib('Elveflow32', 'BFS_Get_Mass_Flow' , BFS_ID_in, MassFlow);


end