function [error] = OB1_Set_Trig(OB1_ID, trigger)
 % Elveflow Library
 % OB1 Device
 % 
 % Set the trigger of the OB1 (0 = 0V, 1 =3,3V)
 
error=calllib('Elveflow64', 'OB1_Set_Trig' , OB1_ID, trigger);


end