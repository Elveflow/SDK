function [error] = OB1_Get_Press(OB1_ID, Channel_1_to_4, Acquire_Data1True0False, Calib_array_in, Pressure, Calib_Array_len)
 % Elveflow Library
 % OB1 Device
 % 
 % 
 % Get the pressure of an OB1 channel. 
 % 
 % Calibration array is required (use Set_Default_Calib if required) and 
 % return a double . Len correspond to the Calib_array_in length. 
 % 
 % If Acquire_data is true, the OB1 acquires ALL regulator AND ALL analog 
 % sensor value. They are stored in the computer memory. Therefore, if several 
 % regulator values (OB1_Get_Press) and/or sensor values (OB1_Get_Sens_Data) 
 % have to be acquired simultaneously, set the Acquire_Data to true only for 
 % the First function. All the other can used the values stored in memory and 
 % are almost instantaneous. 
 
error=calllib('Elveflow32', 'OB1_Get_Press' , OB1_ID, Channel_1_to_4, Acquire_Data1True0False, Calib_array_in, Pressure, Calib_Array_len);


end