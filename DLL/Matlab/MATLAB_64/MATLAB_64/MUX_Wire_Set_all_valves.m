function [error] = MUX_Wire_Set_all_valves(MUX_ID_in, array_valve_in, len)
 % Elveflow Library
 % Mux Device
 % 
 % Valves are set by a array of 16 element. If the valve value is equal or 
 % below 0, valve is close, if it's equal or above 1 the valve is open. If the 
 % array does not contain exactly 16 element nothing happened
 % 
 
error=calllib('Elveflow64', 'MUX_Wire_Set_all_valves' , MUX_ID_in, array_valve_in, len);


end