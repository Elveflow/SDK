function [error] = MUX_DRI_Get_Valve(MUX_DRI_ID_in, selected_Valve)
 % Elveflow Library
 % MUX D-R-I Device
 % 
 % Get the current valve number. If the valve is changing, function returns 0.
 
error=calllib('Elveflow32', 'MUX_DRI_Get_Valve' , MUX_DRI_ID_in, selected_Valve);


end