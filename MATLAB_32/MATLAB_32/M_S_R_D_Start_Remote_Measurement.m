function [error] = M_S_R_D_Start_Remote_Measurement(M_S_R_D_ID)
 % Elveflow Library
 % MSRD Device
 % 
 % Start the monitoring loop for the MSRD device.
 
error=calllib('Elveflow32', 'M_S_R_D_Start_Remote_Measurement' , M_S_R_D_ID);


end