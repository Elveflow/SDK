function [error] = MUX_Set_Trig(MUX_ID_in, Trigger)
 % Elveflow Library
 % Mux Device
 % 
 % Set the Trigger of the MUX device (0=0V, 1=5V).
 
error=calllib('Elveflow32', 'MUX_Set_Trig' , MUX_ID_in, Trigger);


end