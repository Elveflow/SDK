#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "OB1.h"
#include "windows.h"
//#include <Elveflow64.h> //modify the additional include directory
#include "dll/Elveflow64.h"
using namespace std;

int main_OB1()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW errors. 

	////////////////////////
	//
	// Initialization
	//
	////////////////////////

	cout << "device name, regulators and sensors hardcoded in the OB1.cpp file" << endl;
	//OB1_type *myOB1 = new OB1_type;
	int MyOB1_ID = -1; //initialize myOB1ID at negative value (after initialization it should become positive or =0)
					   //initialize the OB1 -> Use NIMAX to determine the device name
					   //avoid non alphanumeric characters in device name
	error = OB1_Initialization("COM3", 1, 1, 0, 0, &MyOB1_ID);
	
	Check_Error(error);//error sent if not recognized
	//add a sensor
	//error = OB1_Add_Sens(MyOB1_ID, 1,Z_sensor_type_Flow_1000_muL_min, Z_Sensor_digit_analog_Digital, Z_Sensor_FSD_Calib_H2O, Z_D_F_S_Resolution__16Bit,0);// Add digital flow sensor with H2O Calibration (CustomSens_Voltage_5_to_25 only works with CustomSensors and OB1 from 2020 and after)
	// ! ! ! If the sensor is not recognized a pop up will indicate it
	//Check_Error(error);//error sent if not recognized
	////////////////////////
	//
	// Choose calibration
	//
	//////////////////////// 
	double *Calibration = new double[1000];// define the calibration (array of double). Size can vary, depending on the instrument but 1000 is always enough.
	do {//choose calibration
		cout << "Choose OB1 calibration: default , load , new" << endl;
		getline(cin, answer);
	} while (!(answer == "default" || answer == "load" || answer == "new"));
	char *Calib_path = "C:\\Users\\Public\\Desktop\\Calibration\\Calib.txt";
	//apply the desired calibration
	if (answer == "default")
	{
		//OB1_Calib_Default(Calibration, 1000); //use default calibration
	}
	else if (answer == "load")
	{
		OB1_Calib_Load(MyOB1_ID, Calib_path);//load the file contained in the path, if no path or non valid path, prompt ask the user to choose the file
	}
	else if (answer == "new")
	{
		cout << "wait ~2 minutes" << endl;
		OB1_Calib(MyOB1_ID);//Perform calibration ! ! ! Take about 2 minutes ! ! !
		error = OB1_Calib_Save(MyOB1_ID, Calib_path); //save calibration in the selected path, if no path or non valid path, open prompt to ask the file name
		Check_Error(error);
	}


	////////////////////////
	//
	// Main loop 
	//
	////////////////////////
	int channel = 0;
	int channel_sensor = 0;
	int target = 0;
	double set_pressure = 0;
	double* get_pressure = new double[4];
	double* set_all_pressure = new double[4];
	double get_Sens_data = 0;
	double get_Reg_data = 0;
	float P = 0.0;
	float I = 0.0;
	int reset = 0;
	int trigger = 0;
	int running = 0;
	string answer_trigger = "";

	do {//main loop

		do {//loop to choose what to do
			cout << "\nChoose what to do: set_p, get_trig, set_trig, add_pid, read_channel, set_sensor or exit" << endl;
			getline(cin, answer);
		} while (!(answer == "set_p" || answer == "get_trig" || answer == "set_trig" || answer == " add_pid" || answer == "read_channel" || answer == "set_sensor" || answer == "exit"));

		if (answer == "set_p")
		{
			//ask the target pressure and the channel, and set the value
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "value (mbar)" << endl;
			cin >> set_pressure;
			getline(cin, answer);//remove CR
			OB1_Set_Press(MyOB1_ID, channel, set_pressure);
		}

		if (answer == "get_trig")
		{
			string trigger_string = "";
			OB1_Get_Trig(MyOB1_ID, &trigger);
			if (trigger == 0) trigger_string = "low";
			else trigger_string = "high";
			cout << "trigger is " << trigger_string << endl;

		}

		if (answer == "set_trig")
		{
			//ask the trigger to the user
			do
			{
				cout << "new value (high or low)" << endl;
				getline(cin, answer_trigger);
			} while (!(answer_trigger == "high" || answer_trigger == "low"));
			if (answer_trigger == "high")
			{
				OB1_Set_Trig(MyOB1_ID, 1);
			}
			else
			{
				OB1_Set_Trig(MyOB1_ID, 0);
			}
		}

		if (answer == "add_pid")
		{
			//ask the channels used for regulator and sensor for PID
			cout << "channel used for regulator : channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "channel used for sensor : channel (1 to 4)?" << endl;
			cin >> channel_sensor;
			getline(cin, answer);//remove CR
			PID_Add_Remote(MyOB1_ID, channel, MyOB1_ID, channel_sensor, 10.0, 0.1, 1);
		}

		if (answer == "read_channel")
		{
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			OB1_Get_Data(MyOB1_ID, channel, &get_Reg_data, &get_Sens_data);
			cout << "Regulator/Sensor : " << channel << ";" << get_Reg_data <<";"<< get_Sens_data << endl;
			
		}

		if (answer == "set_sensor")
		{
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "Select sensor target :" << endl;
			cin >> target;
			getline(cin, answer);//remove CR
			OB1_Set_Sens(MyOB1_ID, channel, target);
			
		}

	

	} while (!(answer == "exit"));//stop if exit

	OB1_Destructor(MyOB1_ID);
	system("PAUSE");
	return 0;
}






