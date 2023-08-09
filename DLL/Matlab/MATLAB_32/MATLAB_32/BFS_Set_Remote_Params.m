function [error] = BFS_Set_Remote_Params(BFS_ID, Filter, M_temp, M_density)
 % Elveflow Library
 % BFS Device
 % 
 % Modify the parameters of the remote monitoring loop:
 % M_density: a new measure of the density will be taken before each flow 
 % measurement
 % M_temp: a new temperature measurement will be taken after each flow 
 % measurement
 % Filter: change the filter used to measure the flow
 
error=calllib('Elveflow32', 'BFS_Set_Remote_Params' , BFS_ID, Filter, M_temp, M_density);


end