function [error] = MUX_Set_indiv_valve(MUX_ID_in, Input, Ouput, OpenClose)
 % Elveflow Library
 % Mux Device
 % 
 % Set the state of one valve of the instrument. The desired valve is 
 % addressed using Input and Output parameter which corresponds to the 
 % fluidics inputs and outputs of the instrument. 
 
error=calllib('Elveflow64', 'MUX_Set_indiv_valve' , MUX_ID_in, Input, Ouput, OpenClose);


end