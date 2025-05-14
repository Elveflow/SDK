function [error] = MUX_Get_valves_Type(MUX_ID_in, Types_array, longueur)
 % Elveflow Library
 % Mux Device
 % 
 % Get valve type plugged into your MUX Wire
 % 
 % 
 
error=calllib('Elveflow32', 'MUX_Get_valves_Type' , MUX_ID_in, Types_array, longueur);


end