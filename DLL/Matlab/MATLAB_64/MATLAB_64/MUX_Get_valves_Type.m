function [error] = MUX_Get_valves_Type(MUX_ID_in, Types_array, len)
 % Elveflow Library
 % Mux Device
 % 
 % Get valve type plugged into your MUX Wire
 % 
 % 
 
error=calllib('Elveflow64', 'MUX_Get_valves_Type' , MUX_ID_in, Types_array, len);


end