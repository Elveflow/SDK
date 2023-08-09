function [error] = OB1_Get_Trig(OB1_ID, Trigger)
 % Elveflow Library
 % OB1 Device
 % 
 % Get the trigger of the OB1 (0 = 0V, 1 =3,3V)
 
error=calllib('Elveflow32', 'OB1_Get_Trig' , OB1_ID, Trigger);


end