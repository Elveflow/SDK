function [error] = BFS_Set_Filter(BFS_ID_in, Filter_value)
 % Elveflow Library
 % BFS Device
 % 
 % Set the instruement Filter. 0.000001= maximum filter -> slow change but 
 % very low noise.  1= no filter-> fast change but noisy. 
 % 
 % Default value is 0.1  
 
error=calllib('Elveflow64', 'BFS_Set_Filter' , BFS_ID_in, Filter_value);


end