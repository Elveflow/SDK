function [error] = BFS_Zero(BFS_ID_in)
 % Elveflow Library
 % BFS Device
 % 
 % Perform zero calibration of the BFS. Ensure that there is no flow when 
 % performed; it is advised to use valves.
 % The calibration procedure is finished when the green LED stop blinking.
 
error=calllib('Elveflow64', 'BFS_Zero' , BFS_ID_in);


end