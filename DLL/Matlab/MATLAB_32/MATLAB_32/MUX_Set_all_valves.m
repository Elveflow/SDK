function [error] = MUX_Set_all_valves(MUX_ID_in, array_valve_in, len)
 % Elveflow Library
 % Mux Device
 % 
 % Valves are set by a array of 16 element. If the valve value is equal or 
 % below 0, valve is close, if it's equal or above 1 the valve is open. The 
 % index in the array indicate the selected  valve as shown below : 
 % 0   1   2   3
 % 4   5   6   7
 % 8   9   10  11
 % 12  13  14  15
 % If the array does not contain exactly 16 element nothing happened
 % 
 
error=calllib('Elveflow32', 'MUX_Set_all_valves' , MUX_ID_in, array_valve_in, len);


end