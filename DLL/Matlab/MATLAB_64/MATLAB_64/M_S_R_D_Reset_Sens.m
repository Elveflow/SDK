function [error] = M_S_R_D_Reset_Sens(M_S_R_D_ID)
 % Warning: advanced feature. Reset digital sensor communication from the 
 % selected channel. Select again resolution and calibration type 
 % (H2O/Isopro).
 
error=calllib('Elveflow64', 'M_S_R_D_Reset_Sens' , M_S_R_D_ID);


end