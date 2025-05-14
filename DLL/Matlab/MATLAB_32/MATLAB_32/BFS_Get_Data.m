function [error] = BFS_Get_Data(BFS_ID, Flow, Temperature, Density)
 % Elveflow Library
 % BFS Device
 % 
 % Read the sensors from the remote monitoring loop:
 % Units: Flow sensor: µl/min
 %            Density: g/m3
 %            Temperature: Celcius
 
error=calllib('Elveflow32', 'BFS_Get_Data' , BFS_ID, Flow, Temperature, Density);


end