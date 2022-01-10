function [error] = OB1_Destructor(OB1_ID)
 % Elveflow Library
 % OB1 Device
 % 
 % Close communication with OB1
 
error=calllib('Elveflow32', 'OB1_Destructor' , OB1_ID);


end