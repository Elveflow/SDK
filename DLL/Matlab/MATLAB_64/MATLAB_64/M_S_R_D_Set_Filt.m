function [error] = M_S_R_D_Set_Filt(M_S_R_D_ID, Channel_1_to_4, FilterRunning)
 % Elveflow Library
 % MSRD Device
 % 
 % Set filter for the corresponding channel.
 
error=calllib('Elveflow64', 'M_S_R_D_Set_Filt' , M_S_R_D_ID, Channel_1_to_4, FilterRunning);


end