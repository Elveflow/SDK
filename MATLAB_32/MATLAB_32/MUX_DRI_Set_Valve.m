function [error] = MUX_DRI_Set_Valve(MUX_DRI_ID_in, selected_Valve, Rotation)
 % Elveflow Library
 % MUX D-R-I Device
 % 
 % Switch the MUX Distribution, Distributor, Recirculation or Injection to the 
 % desired valve.
 % For MUX Distribution 12, between 1-12.
 % For MUX Distributor (6 or 10 valves), between 1-6 or 1-10.
 % For MUX Recirculation 6 or MUX Injection (6 valves), the two states are 1 
 % or 2.
 % 
 % Rotation indicates the path the valve will perform to select a valve, 
 % either shortest 0, clockwise 1 or counter clockwise 2.
 
error=calllib('Elveflow32', 'MUX_DRI_Set_Valve' , MUX_DRI_ID_in, selected_Valve, Rotation);


end