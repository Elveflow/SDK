function [error] = BFS_Get_Flow(BFS_ID_in, Flow)
 % Elveflow Library
 % BFS Device
 % 
 % Measure thefluid flow in (microL/min). !!! This function required an 
 % earlier density measurement!!! The density can either be measured only once 
 % at the beginning of the experiment (ensure that the fluid flow through the 
 % sensor prior to density measurement), or before every flow measurement if 
 % the density might change. If you get +inf or -inf, the density wasn't 
 % correctly measured. 
 
error=calllib('Elveflow64', 'BFS_Get_Flow' , BFS_ID_in, Flow);


end