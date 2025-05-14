function [error] = MUX_Set_valves_Type(MUX_ID_in, ValveNb, Type)
 % Elveflow Library
 % Mux Device
 % 
 % Set the vavle type.
 % This function is available for MUX Wire V3 using custom Valves or Valve V2.
 % Valve V3 type are automatically recognized by the MUX
 % 
 % ValveNB (MUX port where your valve is plugged)
 % Type (Type of valve plugged)
 % 
 
error=calllib('Elveflow64', 'MUX_Set_valves_Type' , MUX_ID_in, ValveNb, Type);


end