function [error] = M_S_R_D_Destructor(M_S_R_D_ID)
 % Elveflow Library
 % MSRD Device
 % 
 % Close communication with MSRD
 
error=calllib('Elveflow32', 'M_S_R_D_Destructor' , M_S_R_D_ID);


end