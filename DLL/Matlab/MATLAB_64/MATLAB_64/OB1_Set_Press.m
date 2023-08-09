function [error] = OB1_Set_Press(OB1_ID, Channel_1_to_4, Pressure, Calib_array_in, Calib_Array_len)
 % Elveflow Library
 % OB1 Device
 % 
 % Set the pressure of the OB1 selected channel, Calibration array is required 
 % (use Set_Default_Calib if required). Len correspond to the Calib_array_in 
 % length.
 
error=calllib('Elveflow64', 'OB1_Set_Press' , OB1_ID, Channel_1_to_4, Pressure, Calib_array_in, Calib_Array_len);


end