function [error] = OB1_Reset_Digit_Sens(OB1_ID, Channel_1_to_4)
 % Warning: advanced feature. Reset digital sensor communication from the 
 % selected channel. Select again resolution and calibration type 
 % (H2O/Isopro).
 
error=calllib('Elveflow64', 'OB1_Reset_Digit_Sens' , OB1_ID, Channel_1_to_4);


end