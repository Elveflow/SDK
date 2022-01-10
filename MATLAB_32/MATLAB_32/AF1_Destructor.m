function [error] = AF1_Destructor(AF1_ID_in)
 % Elveflow Library
 % AF1 Device
 % 
 % Close Communication with AF1
 
error=calllib('Elveflow32', 'AF1_Destructor' , AF1_ID_in);


end