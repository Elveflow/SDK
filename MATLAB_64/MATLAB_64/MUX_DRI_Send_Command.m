function [error, Answer] = MUX_DRI_Send_Command(MUX_DRI_ID_in, Action, Answer, len)
 % Elveflow Library
 % MUX D-R-I Device
 % 
 % !This function only works for MUX Distribution 12 or Recirculation 6!
 % 
 % Get the Serial Number or Home the valve. len is the length of the Answer. 
 % Remember that Home the valve take several seconds.
 % 
 % Home the valve is necessary as an initialization step before using the 
 % valve for a session.
 
[error, Answer] =calllib('Elveflow64', 'MUX_DRI_Send_Command' , MUX_DRI_ID_in, Action, Answer, len);


end