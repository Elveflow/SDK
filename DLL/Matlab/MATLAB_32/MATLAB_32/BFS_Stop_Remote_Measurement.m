function [error] = BFS_Stop_Remote_Measurement(BFS_ID)
 % Elveflow Library
 % BFS Device
 % 
 % Stop the monitoring loop for the BFS device.
 
error=calllib('Elveflow32', 'BFS_Stop_Remote_Measurement' , BFS_ID);


end