#include "extcode.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef uint16_t  Z_regulator_type;
#define Z_regulator_type_none 0
#define Z_regulator_type__0_200_mbar 1
#define Z_regulator_type__0_2000_mbar 2
#define Z_regulator_type__0_8000_mbar 3
#define Z_regulator_type_m1000_1000_mbar 4
#define Z_regulator_type_m1000_6000_mbar 5
typedef uint16_t  Z_MUX_DRI_Rotation;
#define Z_MUX_DRI_Rotation_Shortest 0
#define Z_MUX_DRI_Rotation_Clockwise 1
#define Z_MUX_DRI_Rotation_CounterClockwise 2
typedef uint16_t  Z_sensor_type;
#define Z_sensor_type_none 0
#define Z_sensor_type_Flow_1_5_muL_min 1
#define Z_sensor_type_Flow_7_muL_min 2
#define Z_sensor_type_Flow_50_muL_min 3
#define Z_sensor_type_Flow_80_muL_min 4
#define Z_sensor_type_Flow_1000_muL_min 5
#define Z_sensor_type_Flow_5000_muL_min 6
#define Z_sensor_type_Press_70_mbar 7
#define Z_sensor_type_Press_340_mbar 8
#define Z_sensor_type_Press_1_bar 9
#define Z_sensor_type_Press_2_bar 10
#define Z_sensor_type_Press_7_bar 11
#define Z_sensor_type_Press_16_bar 12
#define Z_sensor_type_Level 13
#define Z_sensor_type_Custom 14
typedef uint16_t  Z_Sensor_digit_analog;
#define Z_Sensor_digit_analog_Analog 0
#define Z_Sensor_digit_analog_Digital 1
typedef uint16_t  Z_Sensor_FSD_Calib;
#define Z_Sensor_FSD_Calib_H2O 0
#define Z_Sensor_FSD_Calib_IPA 1
typedef uint16_t  Z_D_F_S_Resolution;
#define Z_D_F_S_Resolution__9Bit 0
#define Z_D_F_S_Resolution__10Bit 1
#define Z_D_F_S_Resolution__11Bit 2
#define Z_D_F_S_Resolution__12Bit 3
#define Z_D_F_S_Resolution__13Bit 4
#define Z_D_F_S_Resolution__14Bit 5
#define Z_D_F_S_Resolution__15Bit 6
#define Z_D_F_S_Resolution__16Bit 7
typedef uint16_t  Z_MUX_DRI_Action;
#define Z_MUX_DRI_Action_Home 0
#define Z_MUX_DRI_Action_SerialNumber 1
typedef uint16_t  Z_Trigger_type;
#define Z_Trigger_type_Low 0
#define Z_Trigger_type_High 1
typedef uint16_t  Enum;
#define Enum_UNDEFINED 0
#define Enum__22NormallyClosed 1
#define Enum__22NormallyOpened 2
#define Enum__32Universal 3
#define Enum__22NormallyClosedCustom 4
#define Enum__22NormallyOpenedCustom 5
#define Enum__32UniversalCustom 6

/*!
 * Elveflow Library
 * Mux Device
 * 
 * Initiate the MUX device using device name (could be obtained in NI MAX). It 
 * return the F_S_R ID (number >=0) to be used with other function
 */
int32_t __cdecl MUX_Initialization(char Device_Name[], int32_t *MUX_ID_out);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Valves are set by a array of 16 element. If the valve value is equal or 
 * below 0, valve is close, if it's equal or above 1 the valve is open. The 
 * index in the array indicate the selected  valve as shown below : 
 * 0   1   2   3
 * 4   5   6   7
 * 8   9   10  11
 * 12  13  14  15
 * If the array does not contain exactly 16 element nothing happened
 * 
 */
int32_t __cdecl MUX_Set_all_valves(int32_t MUX_ID_in, 
	int32_t array_valve_in[], int32_t len);
/*!
 * Elveflow Library
 * MUX D-R-I Device
 * 
 * Initiate the MUX Distribution, Distributor, Recirculation or Injection 
 * device using device COM port (ASRLXXX::INSTR where XXX is usually the COM 
 * port that could be found in Windows device manager). It returns the MUX 
 * D-R-I ID (number >=0) to be used with other function.
 */
int32_t __cdecl MUX_DRI_Initialization(char Visa_COM[], 
	int32_t *MUX_DRI_ID_out);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Initialize the OB1 device using device name and regulators type (see SDK 
 * Z_regulator_type for corresponding numbers). It modify the OB1 ID (number 
 * >=0). This ID can be used be used with other function to identify the 
 * targed OB1. If an error occurs during the initialization process, the OB1 
 * ID value will be -1. 
 */
int32_t __cdecl OB1_Initialization(char Device_Name[], 
	Z_regulator_type Reg_Ch_1, Z_regulator_type Reg_Ch_2, 
	Z_regulator_type Reg_Ch_3, Z_regulator_type Reg_Ch_4, int32_t *OB1_ID_out);
/*!
 * Elveflow Library
 * OB1-AF1 Device
 * 
 * Set default Calib in Calib cluster, len is the Calib_Array_out array length
 */
int32_t __cdecl Elveflow_Calibration_Default(double Calib_Array_out[], 
	int32_t len);
/*!
 * Elveflow Library
 * OB1-AF1 Device
 * 
 * Load the calibration file located at Path and returns the calibration 
 * parameters in the Calib_Array_out. len is the Calib_Array_out array length. 
 * The function asks the user to choose the path if Path is not valid, empty 
 * or not a path. The function indicate if the file was found.
 */
int32_t __cdecl Elveflow_Calibration_Load(char Path[], 
	double Calib_Array_out[], int32_t len);
/*!
 * Elveflow Library
 * OB1-AF1 Device
 * 
 * Save the Calibration cluster in the file located at Path. len is the 
 * Calib_Array_in array length. The function prompt the user to choose the 
 * path if Path is not valid, empty or not a path.
 */
int32_t __cdecl Elveflow_Calibration_Save(char Path[], 
	double Calib_Array_in[], int32_t len);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Launch OB1 calibration and return the calibration array. Before 
 * Calibration, ensure that ALL channels are proprely closed with adequate 
 * caps. 
 * Len correspond to the Calib_array_out length.
 */
int32_t __cdecl OB1_Calib(int32_t OB1_ID_in, double Calib_array_out[], 
	int32_t len);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * 
 * Get the pressure of an OB1 channel. 
 * 
 * Calibration array is required (use Set_Default_Calib if required) and 
 * return a double . Len correspond to the Calib_array_in length. 
 * 
 * If Acquire_data is true, the OB1 acquires ALL regulator AND ALL analog 
 * sensor value. They are stored in the computer memory. Therefore, if several 
 * regulator values (OB1_Get_Press) and/or sensor values (OB1_Get_Sens_Data) 
 * have to be acquired simultaneously, set the Acquire_Data to true only for 
 * the First function. All the other can used the values stored in memory and 
 * are almost instantaneous. 
 */
int32_t __cdecl OB1_Get_Press(int32_t OB1_ID, int32_t Channel_1_to_4, 
	int32_t Acquire_Data1True0False, double Calib_array_in[], double *Pressure, 
	int32_t Calib_Array_len);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Set the pressure of the OB1 selected channel, Calibration array is required 
 * (use Set_Default_Calib if required). Len correspond to the Calib_array_in 
 * length.
 */
int32_t __cdecl OB1_Set_Press(int32_t OB1_ID, int32_t Channel_1_to_4, 
	double Pressure, double Calib_array_in[], int32_t Calib_Array_len);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Close communication with OB1
 */
int32_t __cdecl OB1_Destructor(int32_t OB1_ID);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Read the sensor of the requested channel. ! This Function only convert data 
 * that are acquired in OB1_Acquire_data
 * Units : Flow sensor µl/min
 * Pressure : mbar
 * 
 * If Acquire_data is true, the OB1 acquires ALL regulator AND ALL analog 
 * sensor value. They are stored in the computer memory. Therefore, if several 
 * regulator values (OB1_Get_Press) and/or sensor values (OB1_Get_Sens_Data) 
 * have to be acquired simultaneously, set the Acquire_Data to true only for 
 * the First function. All the other can used the values stored in memory and 
 * are almost instantaneous. For Digital Sensor, that required another 
 * communication protocol, this parameter have no impact
 * 
 * NB: For Digital Flow Senor, If the connection is lots, OB1 will be reseted 
 * and the return value will be zero
 */
int32_t __cdecl OB1_Get_Sens_Data(int32_t OB1_ID, int32_t Channel_1_to_4, 
	int32_t Acquire_Data1True0False, double *Sens_Data);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Get the trigger of the OB1 (0 = 0V, 1 =3,3V)
 */
int32_t __cdecl OB1_Get_Trig(int32_t OB1_ID, int32_t *Trigger);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Set the trigger of the OB1 (0 = 0V, 1 =3,3V)
 */
int32_t __cdecl OB1_Set_Trig(int32_t OB1_ID, int32_t trigger);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Close the communication of the MUX device
 */
int32_t __cdecl MUX_Destructor(int32_t MUX_ID_in);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Get the trigger of the MUX device (0=0V, 1=5V).
 */
int32_t __cdecl MUX_Get_Trig(int32_t MUX_ID_in, int32_t *Trigger);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Set the state of one valve of the instrument. The desired valve is 
 * addressed using Input and Output parameter which corresponds to the 
 * fluidics inputs and outputs of the instrument. 
 */
int32_t __cdecl MUX_Set_indiv_valve(int32_t MUX_ID_in, int32_t Input, 
	int32_t Ouput, int32_t OpenClose);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Set the Trigger of the MUX device (0=0V, 1=5V).
 */
int32_t __cdecl MUX_Set_Trig(int32_t MUX_ID_in, int32_t Trigger);
/*!
 * Elveflow Library
 * MUX D-R-I Device
 * 
 * Close Communication with MUX Distribution, Distributor, Recirculation or 
 * Injection device.
 */
int32_t __cdecl MUX_DRI_Destructor(int32_t MUX_DRI_ID_in);
/*!
 * Elveflow Library
 * MUX D-R-I Device
 * 
 * Get the current valve number. If the valve is changing, function returns 0.
 */
int32_t __cdecl MUX_DRI_Get_Valve(int32_t MUX_DRI_ID_in, 
	int32_t *selected_Valve);
/*!
 * Elveflow Library
 * MUX D-R-I Device
 * 
 * Switch the MUX Distribution, Distributor, Recirculation or Injection to the 
 * desired valve.
 * For MUX Distribution 12, between 1-12.
 * For MUX Distributor (6 or 10 valves), between 1-6 or 1-10.
 * For MUX Recirculation 6 or MUX Injection (6 valves), the two states are 1 
 * or 2.
 * 
 * Rotation indicates the path the valve will perform to select a valve, 
 * either shortest 0, clockwise 1 or counter clockwise 2.
 */
int32_t __cdecl MUX_DRI_Set_Valve(int32_t MUX_DRI_ID_in, 
	int32_t selected_Valve, Z_MUX_DRI_Rotation Rotation);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Add sensor to OB1 device. Select the channel n° (1-4) the sensor type. 
 * 
 * For Flow sensor, the type of communication (Analog/Digital), the 
 * Calibration for digital version (H20 or IPA) should be specify as well as 
 * digital resolution (9 to 16 bits). (see SDK user guide,  Z_sensor_type_type 
 * , Z_sensor_digit_analog, Z_Sensor_FSD_Calib and Z_D_F_S_Resolution for 
 * number correspondance)
 * 
 * For digital version, the sensor type is automatically detected during this 
 * function call. 
 * 
 * For Analog sensor, the calibration parameters is not taken into account. 
 * 
 * If the sensor is not compatible with the OB1 version, or no digital sensor 
 * are detected an error will be thrown as output of the function.
 */
int32_t __cdecl OB1_Add_Sens(int32_t OB1_ID, int32_t Channel_1_to_4, 
	Z_sensor_type SensorType, Z_Sensor_digit_analog DigitalAnalog, 
	Z_Sensor_FSD_Calib FSens_Digit_Calib, 
	Z_D_F_S_Resolution FSens_Digit_Resolution, double CustomSens_Voltage_5_to_25);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Close Communication with BFS device
 */
int32_t __cdecl BFS_Destructor(int32_t BFS_ID_in);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Initiate the BFS device using device com port (ASRLXXX::INSTR where XXX is 
 * the com port that could be found in windows device manager). It return the 
 * BFS ID (number >=0) to be used with other function 
 */
int32_t __cdecl BFS_Initialization(char Visa_COM[], int32_t *BFS_ID_out);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Get fluid density (in g/L) for the BFS defined by the BFS_ID
 */
int32_t __cdecl BFS_Get_Density(int32_t BFS_ID_in, double *Density);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Measure thefluid flow in (microL/min). !!! This function required an 
 * earlier density measurement!!! The density can either be measured only once 
 * at the beginning of the experiment (ensure that the fluid flow through the 
 * sensor prior to density measurement), or before every flow measurement if 
 * the density might change. If you get +inf or -inf, the density wasn't 
 * correctly measured. 
 */
int32_t __cdecl BFS_Get_Flow(int32_t BFS_ID_in, double *Flow);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Get the fluid temperature (in °C) of the BFS defined by the BFS_ID
 */
int32_t __cdecl BFS_Get_Temperature(int32_t BFS_ID_in, double *Temperature);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Set the instruement Filter. 0.000001= maximum filter -> slow change but 
 * very low noise.  1= no filter-> fast change but noisy. 
 * 
 * Default value is 0.1  
 */
int32_t __cdecl BFS_Set_Filter(int32_t BFS_ID_in, double Filter_value);
/*!
 * Elveflow Library - ONLY FOR ILLUSTRATION - 
 * OB1 Devices
 * 
 * This function is only provided for illustration purpose, to explain how to 
 * do your own feedback loop. Elveflow does not guarante neither efficient nor 
 * optimum regulation with this illustration of PI regulator . With this 
 * function the PI parameters have to be tuned for every regulator and every 
 * microfluidic circuit.   
 * 
 * In this function need to be initiate with a first call where PID_ID =-1. 
 * The PID_out will provide the new created PID_ID. This ID should be use in 
 * further call. 
 * 
 * General remarks of this PI regulator :
 * 
 * The error "e" is calculate for every step as e=target value-actual value
 * There are 2 contributions to a PI regulator: proportional contribution 
 * which only depend on this step and  Prop=e*P and integral part which is the 
 * "memory" of the regulator. This value is calculated as 
 * Integ=integral(I*e*dt) and can be reset. 
 *   
 */
int32_t __cdecl Elveflow_EXAMPLE_PID(int32_t PID_ID_in, double currentValue, 
	int32_t Reset, double P, double I, double targetValue, int32_t *PID_ID_out, 
	double *value);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Valves are set by a array of 16 element. If the valve value is equal or 
 * below 0, valve is close, if it's equal or above 1 the valve is open. If the 
 * array does not contain exactly 16 element nothing happened
 * 
 */
int32_t __cdecl MUX_Wire_Set_all_valves(int32_t MUX_ID_in, 
	int32_t array_valve_in[], int32_t len);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Set the pressure of all the channel of the selected OB1. Calibration array 
 * is required (use Set_Default_Calib if required). Calib_Array_Len correspond 
 * to the Calib_array_in length. It uses an array as pressures input. 
 * Pressure_Array_Len corresponds to the the pressure input array. The first 
 * number of the array correspond to the first channel, the seconds number to 
 * the seconds channels and so on. All the number above 4 are not taken into 
 * account. 
 * 
 * If only One channel need to be set, use OB1_Set_Pressure.
 */
int32_t __cdecl OB1_Set_All_Press(int32_t OB1_ID, double Pressure_array_in[], 
	double Calib_array_in[], int32_t Pressure_Array_Len, int32_t Calib_Array_Len);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Perform zero calibration of the BFS. Ensure that there is no flow when 
 * performed; it is advised to use valves.
 * The calibration procedure is finished when the green LED stop blinking.
 */
int32_t __cdecl BFS_Zeroing(int32_t BFS_ID_in);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Get the fluid mass flow in (g/h) of the BFS defined by the BFS_ID
 */
int32_t __cdecl BFS_Get_Mass_Flow(int32_t BFS_ID_in, double *MassFlow);
/*!
 * Warning: advanced feature. Reset OB1 communication for pressure and flow.
 */
int32_t __cdecl OB1_Reset_Instr(int32_t OB1_ID);
/*!
 * Warning: advanced feature. Reset digital sensor communication from the 
 * selected channel. Select again resolution and calibration type 
 * (H2O/Isopro).
 */
int32_t __cdecl OB1_Reset_Digit_Sens(int32_t OB1_ID, int32_t Channel_1_to_4);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Initialize the Sensor Reader device able to read digital sensors (MSRD) 
 * using device name and sensors type (see SDK Z_sensor_type for corresponding 
 * numbers). It modify the MSRD ID (number >=0). This ID can be used with 
 * other function to identify the targeted MSRD. If an error occurs during the 
 * initialization process, the MSRD ID value will be -1. 
 * 
 * Initiate the communication with the Sensor Reader able to read digital 
 * sensors (MSRD). This VI generates an identification cluster of the 
 * instrument to be used with other VIs.
 * 
 * NB: Sensor type has to be written here in addition to the "Add_Sens".
 * NB 2: Sensor connected to channel 1-2 and 3-4 have to be the same type 
 * otherwise they will not be taken into account. 
 */
int32_t __cdecl M_S_R_D_Initialization(char Device_Name[], 
	Z_sensor_type Sens_Ch_1, Z_sensor_type Sens_Ch_2, Z_sensor_type Sens_Ch_3, 
	Z_sensor_type Sens_Ch_4, double CustomSens_Voltage_Ch12, 
	double CustomSens_Voltage_Ch34, int32_t *MSRD_ID_out);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Add sensor to MSRD device. Select the channel n° (1-4) the sensor type. 
 * 
 * For Flow sensor, the type of communication (Analog/Digital), the 
 * Calibration for digital version (H20 or IPA) should be specify as well as 
 * digital resolution (9 to 16 bits). (see SDK user guide,  Z_sensor_type_type 
 * , Z_sensor_digit_analog, Z_Sensor_FSD_Calib and Z_D_F_S_Resolution for 
 * number correspondance)
 * 
 * For digital version, the sensor type is automatically detected during this 
 * function call. 
 * 
 * For Analog sensor, the calibration parameters is not taken into account. 
 * 
 * If the sensor is not compatible with the MSRD version, or no digital sensor 
 * are detected an error will be thrown as output of the function.
 * 
 * NB: Sensor type has to be the same as in the "Initialization" step.
 */
int32_t __cdecl M_S_R_D_Add_Sens(int32_t M_S_R_D_ID, int32_t Channel_1_to_4, 
	Z_sensor_type SensorType, Z_Sensor_digit_analog DigitalAnalog, 
	Z_Sensor_FSD_Calib FSens_Digit_Calib, 
	Z_D_F_S_Resolution FSens_Digit_Resolution);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Close communication with MSRD
 */
int32_t __cdecl M_S_R_D_Destructor(int32_t M_S_R_D_ID);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Read the sensor of the requested channel.s
 * Units: Flow sensor: µl/min
 * Pressure: mbar
 * 
 * NB: For Digital Flow Senor, If the connection is lost, MSRD will be reseted 
 * and the return value will be zero
 */
int32_t __cdecl M_S_R_D_Get_Sens_Data(int32_t M_S_R_D_ID, 
	int32_t Channel_1_to_4, double *Sens_Data);
/*!
 * Elveflow Library
 * MUX D-R-I Device
 * 
 * !This function only works for MUX Distribution 12 or Recirculation 6!
 * 
 * Get the Serial Number or Home the valve. len is the length of the Answer. 
 * Remember that Home the valve take several seconds.
 * 
 * Home the valve is necessary as an initialization step before using the 
 * valve for a session.
 */
int32_t __cdecl MUX_DRI_Send_Command(int32_t MUX_DRI_ID_in, 
	Z_MUX_DRI_Action Action, char Answer[], int32_t len);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Set filter for the corresponding channel.
 */
int32_t __cdecl M_S_R_D_Set_Filt(int32_t M_S_R_D_ID, int32_t Channel_1_to_4, 
	LVBoolean ONOFF);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Read the sensor and regulator values of the requested channel.
 * Warning: This Function only extracts data obtained in the remote 
 * measurement loop
 * Sensor unit : mbar if pressure sensor, µl/min if flow sensor
 * Regulator unit : mbar
 * 
 * NB: For Digital Flow Senor, If the connection is lost, OB1 will be reseted 
 * and the return value will be zero
 */
int32_t __cdecl OB1_Get_Remote_Data(int32_t OB1_ID, int32_t Channel_1_to_4, 
	double *Reg_Data, double *Sens_Data);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Start a loop running in the background, and automatically reads all sensors 
 * and regulators. No direct call to the OB1 can be made until the Stop 
 * measuring function is called. Until then only functions accessing this loop 
 * (get_remote_data, set_remote_target, remote_triggers) are recommended.
 */
int32_t __cdecl OB1_Start_Remote_Measurement(int32_t OB1_ID, 
	double Calib_array_in[], int32_t len);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Stop the background measure & control loop
 */
int32_t __cdecl OB1_Stop_Remote_Measurement(int32_t OB1_ID);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Set the Target of the OB1 selected channel. Modify the pressure if the PID 
 * is off, or the sensor is a pressure sensor. Modify a flow if the sensor is 
 * a flow sensor and the PID is on.
 */
int32_t __cdecl OB1_Set_Remote_Target(int32_t OB1_ID, int32_t Channel_1_to_4, 
	double Target);
/*!
 * Elveflow Library
 * PID Module
 * 
 * Set to run/pause the selected PID loop. Only works when using the remote 
 * measurement functions.
 */
int32_t __cdecl PID_Set_Running_Remote(int32_t Regulator_ID, 
	int32_t Channel_1_to_4, int32_t Running);
/*!
 * Elveflow Library
 * PID Module
 * 
 * Configure a PID loop between a regulator and a sensor. Only works when 
 * using the remote measurement functions.
 */
int32_t __cdecl PID_Add_Remote(int32_t Regulator_ID, 
	int32_t Regulator_Channel_1_to_4, int32_t ID_Sensor, 
	int32_t Sensor_Channel_1_to_4, double P, double I, int32_t Running);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Start the monitoring loop for the BFS device.
 */
int32_t __cdecl BFS_Start_Remote_Measurement(int32_t BFS_ID);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Stop the monitoring loop for the BFS device.
 */
int32_t __cdecl BFS_Stop_Remote_Measurement(int32_t BFS_ID);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Read the sensors from the remote monitoring loop:
 * Units: Flow sensor: µl/min
 *            Density: g/m3
 *            Temperature: Celcius
 */
int32_t __cdecl BFS_Get_Remote_Data(int32_t BFS_ID, double *Flow, 
	double *Density, double *Temperature);
/*!
 * Elveflow Library
 * BFS Device
 * 
 * Modify the parameters of the remote monitoring loop:
 * M_density: a new measure of the density will be taken before each flow 
 * measurement
 * M_temp: a new temperature measurement will be taken after each flow 
 * measurement
 * Filter: change the filter used to measure the flow
 */
int32_t __cdecl BFS_Set_Remote_Params(int32_t BFS_ID, double Filter, 
	int32_t M_temp, int32_t M_density);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Start the monitoring loop for the MSRD device.
 */
int32_t __cdecl M_S_R_D_Start_Remote_Measurement(int32_t M_S_R_D_ID);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Stop the monitoring loop for the MSRD device.
 */
int32_t __cdecl M_S_R_D_Stop_Remote_Measurement(int32_t M_S_R_D_ID);
/*!
 * Elveflow Library
 * MSRD Device
 * 
 * Read the sensor of the requested channel.s
 * Units: Flow sensor: µl/min
 * Pressure: mbar
 * 
 * NB: For Digital Flow Senor, If the connection is lost, MSRD will be reseted 
 * and the return value will be zero
 */
int32_t __cdecl M_S_R_D_Get_Remote_Data(int32_t M_S_R_D_ID, 
	int32_t Channel_1_to_4, double *Sens_Data);
/*!
 * Elveflow Library
 * OB1 Device
 * 
 * Set the Trigger input and get the Trigger output of the OB1 device.
 */
int32_t __cdecl OB1_Remote_Triggers(int32_t OB1_ID, int32_t TriggerIn, 
	int32_t *TriggerOut);
/*!
 * Elveflow Library
 * PID Module
 * 
 * Change the parameters of the selected PID loop. Only works when using the 
 * remote measurement functions.
 */
int32_t __cdecl PID_Set_Params_Remote(int32_t Regulator_ID, 
	int32_t Channel_1_to_4, int32_t Reset, double P, double I);
/*!
 * Warning: advanced feature. Reset MSRD communication.
 */
int32_t __cdecl M_S_R_D_Reset_Instr(int32_t M_S_R_D_ID);
/*!
 * Warning: advanced feature. Reset digital sensor communication from the 
 * selected channel. Select again resolution and calibration type 
 * (H2O/Isopro).
 */
int32_t __cdecl M_S_R_D_Reset_Sens(int32_t M_S_R_D_ID);
/*!
 * Elveflow_Checkaliases
 */
int32_t __cdecl Elveflow_Checkaliases(void);
/*!
 * Elveflow Library
 * MSR Device
 * 
 * Get the state of the INT trigger (or Trigger IN). If nothing is connected 
 * it returns a High state. 
 * Low=>0V
 * High=>5V
 * 
 * NB: For Digital Flow Senor, If the connection is lost, MSRD will be reseted 
 * and the return value will be zero
 */
int32_t __cdecl M_S_R_D_Get_Trig(int32_t M_S_R_D_ID, 
	Z_Trigger_type *GetTriggerInput);
/*!
 * Elveflow Library
 * MSR Device
 * 
 * Set the trigger OUT of the MSR (HIGH =>5V, LOW => 0V)
 * 
 * NB: only works for the MSR MCU device
 */
int32_t __cdecl M_S_R_D_Set_Trig(int32_t M_S_R_D_ID, 
	Z_Trigger_type SetTriggerOutput);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Get valve type plugged into your MUX Wire
 * 
 * 
 */
int32_t __cdecl MUX_Get_valves_Type(int32_t MUX_ID_in, int32_t Types_array[], 
	int32_t len);
/*!
 * Elveflow Library
 * Mux Device
 * 
 * Set the vavle type.
 * This function is available for MUX Wire V3 using custom Valves or Valve V2.
 * Valve V3 type are automatically recognized by the MUX
 * 
 * ValveNB (MUX port where your valve is plugged)
 * Type (Type of valve plugged)
 * 
 */
int32_t __cdecl MUX_Set_valves_Type(int32_t MUX_ID_in, int32_t ValveNb, 
	Enum Type);

MgErr __cdecl LVDLLStatus(char *errStr, int errStrLen, void *module);

void __cdecl SetExecuteVIsInPrivateExecutionSystem(Bool32 value);

#ifdef __cplusplus
} // extern "C"
#endif

