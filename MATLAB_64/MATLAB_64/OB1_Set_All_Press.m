function [error] = OB1_Set_All_Press(OB1_ID, Pressure_array_in, Calib_array_in, Pressure_Array_Len, Calib_Array_Len)
 % Elveflow Library
 % OB1 Device
 % 
 % Set the pressure of all the channel of the selected OB1. Calibration array 
 % is required (use Set_Default_Calib if required). Calib_Array_Len correspond 
 % to the Calib_array_in length. It uses an array as pressures input. 
 % Pressure_Array_Len corresponds to the the pressure input array. The first 
 % number of the array correspond to the first channel, the seconds number to 
 % the seconds channels and so on. All the number above 4 are not taken into 
 % account. 
 % 
 % If only One channel need to be set, use OB1_Set_Pressure.
 
error=calllib('Elveflow64', 'OB1_Set_All_Press' , OB1_ID, Pressure_array_in, Calib_array_in, Pressure_Array_Len, Calib_Array_Len);


end