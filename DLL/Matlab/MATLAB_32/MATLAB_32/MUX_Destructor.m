function [error] = MUX_Destructor(MUX_ID_in)
 % Elveflow Library
 % Mux Device
 % 
 % Close the communication of the MUX device
 
error=calllib('Elveflow32', 'MUX_Destructor' , MUX_ID_in);


end