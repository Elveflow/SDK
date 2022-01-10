function [error] = BFS_Start_Remote_Measurement(BFS_ID)
 % Elveflow Library
 % BFS Device
 % 
 % Start the monitoring loop for the BFS device.
 
error=calllib('Elveflow32', 'BFS_Start_Remote_Measurement' , BFS_ID);


end