function [error] = BFS_Get_Remote_Data(BFS_ID, Temperature, Density, Flow)
 % Elveflow Library
 % BFS Device
 % 
 % Read the sensors from the remote monitoring loop:
 % Units: Flow sensor: µl/min
 %            Density: g/m3
 %            Temperature: Celcius
 
error=calllib('Elveflow32', 'BFS_Get_Remote_Data' , BFS_ID, Temperature, Density, Flow);


end