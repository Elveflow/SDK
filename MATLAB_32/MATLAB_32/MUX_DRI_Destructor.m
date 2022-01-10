function [error] = MUX_DRI_Destructor(MUX_DRI_ID_in)
 % Elveflow Library
 % MUX D-R-I Device
 % 
 % Close Communication with MUX Distribution, Distributor, Recirculation or 
 % Injection device.
 
error=calllib('Elveflow32', 'MUX_DRI_Destructor' , MUX_DRI_ID_in);


end