function [error] = OB1_Add_Sens(OB1_ID, Channel_1_to_4, SensorType, DigitalAnalog, FSens_Digit_Calib, FSens_Digit_Resolution, CustomSens_Voltage_5_to_25)
 % Elveflow Library
 % OB1 Device
 % 
 % Add sensor to OB1 device. Select the channel n° (1-4) the sensor type. 
 % 
 % For Flow sensor, the type of communication (Analog/Digital), the 
 % Calibration for digital version (H20 or IPA) should be specify as well as 
 % digital resolution (9 to 16 bits). (see SDK user guide,  Z_sensor_type_type 
 % , Z_sensor_digit_analog, Z_Sensor_FSD_Calib and Z_D_F_S_Resolution for 
 % number correspondance)
 % 
 % For digital version, the sensor type is automatically detected during this 
 % function call. 
 % 
 % For Analog sensor, the calibration parameters is not taken into account. 
 % 
 % If the sensor is not compatible with the OB1 version, or no digital sensor 
 % are detected an error will be thrown as output of the function.
 
error=calllib('Elveflow32', 'OB1_Add_Sens' , OB1_ID, Channel_1_to_4, SensorType, DigitalAnalog, FSens_Digit_Calib, FSens_Digit_Resolution, CustomSens_Voltage_5_to_25);


end