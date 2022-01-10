function [error] = M_S_R_D_Set_Filt(M_S_R_D_ID, Channel_1_to_4, ONOFF)
 % Elveflow Library
 % MSRD Device
 % 
 % Set filter for the corresponding channel.
 
error=calllib('Elveflow32', 'M_S_R_D_Set_Filt' , M_S_R_D_ID, Channel_1_to_4, ONOFF);


end