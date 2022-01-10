function [error] = F_S_R_Destructor(F_S_Reader_ID_in)
 % Elveflow Library
 % Sensor Reader or Flow Reader Device
 % 
 % Close Communication with F_S_R.
 
error=calllib('Elveflow32', 'F_S_R_Destructor' , F_S_Reader_ID_in);


end