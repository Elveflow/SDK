function [error] = MUX_Get_Trig(MUX_ID_in, Trigger)
 % Elveflow Library
 % Mux Device
 % 
 % Get the trigger of the MUX device (0=0V, 1=5V).
 
error=calllib('Elveflow32', 'MUX_Get_Trig' , MUX_ID_in, Trigger);


end