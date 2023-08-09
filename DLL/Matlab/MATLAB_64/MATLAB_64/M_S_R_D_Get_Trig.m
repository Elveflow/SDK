function [error] = M_S_R_D_Get_Trig(M_S_R_D_ID, GetTriggerInput)
 % Elveflow Library
 % MSR Device
 % 
 % Get the state of the INT trigger (or Trigger IN). If nothing is connected 
 % it returns a High state. 
 % Low=>0V
 % High=>5V
 % 
 % NB: For Digital Flow Senor, If the connection is lost, MSRD will be reseted 
 % and the return value will be zero
 
error=calllib('Elveflow64', 'M_S_R_D_Get_Trig' , M_S_R_D_ID, GetTriggerInput);


end