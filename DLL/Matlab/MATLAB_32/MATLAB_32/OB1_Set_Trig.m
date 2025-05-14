function [error] = OB1_Set_Trig(OB1_ID, TriggerIn)
 % Elveflow Library
 % OB1 Device
 % 
 % Set the trigger of the OB1 (0 = 0V, 1 =3,3V for MK3 devices, 5V for MK4 
 % devices)
 
error=calllib('Elveflow32', 'OB1_Set_Trig' , OB1_ID, TriggerIn);


end