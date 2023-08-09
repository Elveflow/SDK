function [error] = M_S_R_D_Set_Trig(M_S_R_D_ID, SetTriggerOutput)
 % Elveflow Library
 % MSR Device
 % 
 % Set the trigger OUT of the MSR (HIGH =>5V, LOW => 0V)
 % 
 % NB: only works for the MSR MCU device
 
error=calllib('Elveflow64', 'M_S_R_D_Set_Trig' , M_S_R_D_ID, SetTriggerOutput);


end