#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "OB1.h"
#include "windows.h"
#include <Elveflow64.h> //modify the additional include directory
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
	error = OB1_Initialization("01C9D9C3", Z_regulator_type__0_200_mbar, Z_regulator_type__0_2000_mbar, Z_regulator_type_m1000_1000_mbar, Z_regulator_type__0_8000_mbar, &MyOB1_ID);
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

	//apply the desired calibration
	if (answer == "default")
	{
		Elveflow_Calibration_Default(Calibration, 1000); //use default calibration
	}
	else if (answer == "load")
	{
		Elveflow_Calibration_Load("", Calibration, 1000);//load the file contained in the path, if no path or non valid path, prompt ask the user to choose the file
	}
	else if (answer == "new")
	{
		cout << "wait ~2 minutes" << endl;
		OB1_Calib(MyOB1_ID, Calibration, 1000);//Perform calibration ! ! ! Take about 2 minutes ! ! !
		error = Elveflow_Calibration_Save("", Calibration, 1000); //save calibration in the selected path, if no path or non valid path, open prompt to ask the file name
		Check_Error(error);
	}


	////////////////////////
	//
	// Main loop 
	//
	////////////////////////
	int channel = 0;
	int channel_sensor = 0;
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
			cout << "\nChoose what to do: get pressure, set pressure, get sensor, set trigger, get trigger, set all pressure, get several sens and reg, test acquisition speed, add pid, run pause pid, start, stop, read channel, set target, set parameters or exit" << endl;
			getline(cin, answer);
		} while (!(answer == "get pressure" || answer == "get several sens and reg" || answer == "set pressure" || answer == "set all pressure" || answer == "get sensor" || answer == "get trigger" || answer == "set trigger" || answer == "exit" || answer == "test acquisition speed" || answer == "add pid" || answer == "start" || answer == "stop" || answer == "read channel" || answer == "set target" || answer == "run pause pid" || answer == "set parameters" ));

		if (answer == "get pressure")
		{
			//ask the channel, and read the value
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			OB1_Get_Press(MyOB1_ID, channel, 1, Calibration, get_pressure, 1000);//use pointer
			cout << "P channel " << channel << ": " << *get_pressure << " mbar" << endl;
		}

		if (answer == "set pressure")
		{
			//ask the target pressure and the channel, and set the value
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "value (mbar)" << endl;
			cin >> set_pressure;
			getline(cin, answer);//remove CR
			OB1_Set_Press(MyOB1_ID, channel, set_pressure, Calibration, 1000);
		}

		if (answer == "get sensor")
		{
			//ask the channel, and read the value
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			OB1_Get_Sens_Data(MyOB1_ID, channel, 1, &get_Sens_data);//use pointer
			cout << "channel " << channel << ": " << get_Sens_data << " µl/min" << endl;
		}

		if (answer == "set trigger")
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

		if (answer == "get trigger")
		{
			string trigger_string = "";
			OB1_Get_Trig(MyOB1_ID, &trigger);
			if (trigger == 0) trigger_string = "low";
			else trigger_string = "high";
			cout << "trigger is " << trigger_string << endl;

		}

		if (answer == "set all pressure")
		{
			//ask the target pressure and the channel, and set the value
			cout << "set the pressure ( same for all channels) in mbar" << endl;
			cin >> set_pressure;
			getline(cin, answer);//remove CR
			for (int i = 0; i < 4; i++)//init the pressure array
			{
				set_all_pressure[i] = set_pressure;//create the array with all data
			}
			OB1_Set_All_Press(MyOB1_ID, set_all_pressure, Calibration, 4, 1000);
		}

		if (answer == "get several sens and reg")
		{
			//get all the channels and the sensors, it takes about 2ms
			channel = 1;
			OB1_Get_Press(MyOB1_ID, channel, 1, Calibration, get_pressure, 1000);//channel 1; Acquire_Data=1 -> Acquire all the analog data
			cout << "P channel " << channel << ": " << *get_pressure << "mbar" << endl;
			for (channel = 2; channel < 5; channel++)//read all other pressure WITHOUT acquiring new data (use the one saved in memory by the first OB1_Get_Press function)
			{
				OB1_Get_Press(MyOB1_ID, channel, 0, Calibration, get_pressure, 1000);//Acquire_Data=0 = use the data in memory
				cout << "P channel " << channel << ": " << *get_pressure << "mbar" << endl;
			}
			for (channel = 1; channel < 5; channel++)//read all analog sensor WITHOUT acquiring new data (use the one saved in memory by the first OB1_Get_Press function). If Digital sensor was added, the acquisition is made by those function (not by the first OB1_Get_Press) and takes about 10 ms
			{
				OB1_Get_Sens_Data(MyOB1_ID, channel, 0, &get_Sens_data);// Acquire_Data=0 = use the data in memory
				cout << "Sens channel " << channel << ": " << get_Sens_data << "µL/min or mbar" << endl;
			}
		}

		if (answer == "test acquisition speed")
		{
			string text = "";
			time_t time_before;
			time_t time_after;
			//read pressure of 4 channels
			SYSTEMTIME TIME_START;
			SYSTEMTIME TIME_ACTUAL;
			OB1_Set_Press(MyOB1_ID, 1, 10, Calibration, 1000);//reset pressure channel 1
			Sleep(1000);//sleep for 1 Second
			OB1_Set_Press(MyOB1_ID, 1, 150, Calibration, 1000);//reset pressure channel 1
			GetSystemTime(&TIME_START);
			for (int j = 0; j < 50; j++)
			{
				//cout << time;
				OB1_Get_Press(MyOB1_ID, 1, 1, Calibration, get_pressure, 1000);//acquire data (Acquire_Data=1) and get the regulator value
				GetSystemTime(&TIME_ACTUAL);
				//*
				text += to_string(TIME_ACTUAL.wMilliseconds - TIME_START.wMilliseconds + (TIME_ACTUAL.wSecond - TIME_START.wSecond) * 1000) + " ms\t";
				for (int i = 0; i < 1; i++)//print only the first channel
				{
					text += "channel " + to_string(i+1) + ": " + to_string(get_pressure[i]) + " mbar\t";//
				}
				text += "\n";
				//text += to_string(TIME_ACTUAL.wMilliseconds - TIME_START.wMilliseconds + (TIME_ACTUAL.wSecond - TIME_START.wSecond) * 1000) + " ms\t press set to 1000\n";

				//Sleep(5);//*/
			}
			cout << text;
		}

		if (answer == "add pid")
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

		if (answer == "run pause pid")
		{
			//ask the channels used for regulator and sensor for PID
			cout << "channel used for regulator : channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "Run or Stop ? (write 1 or 0)" << endl;
			cin >> running;
			getline(cin, answer);//remove CR

			PID_Set_Running_Remote(MyOB1_ID, channel, running);
		}

		if (answer == "start")
		{
			OB1_Start_Remote_Measurement(MyOB1_ID, Calibration, 1000);
		}

		if (answer == "stop")
		{
			OB1_Stop_Remote_Measurement(MyOB1_ID);
		}

		if (answer == "read channel")
		{
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			OB1_Get_Remote_Data(MyOB1_ID, channel, &get_Reg_data, &get_Sens_data);
			cout << "Regulator " << channel << ": " << get_Reg_data << " µl/min" << endl;
			cout << "Sensor " << channel << ": " << get_Sens_data << " µl/min" << endl;
		}

		if (answer == "set target")
		{
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "select pressure (-1000 to 8000 mbars) :" << endl;
			cin >> set_pressure;
			getline(cin, answer);//remove CR
			OB1_Set_Remote_Target(MyOB1_ID, channel, set_pressure);
		}

		if (answer == "set parameters")
		{
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			getline(cin, answer);//remove CR
			cout << "select P :" << endl;
			cin >> P;
			getline(cin, answer);//remove CR
			cout << "select I :" << endl;
			cin >> I;
			getline(cin, answer);//remove CR
			cout << "Reset (1) or not (0)?" << endl;
			cin >> reset;
			getline(cin, answer);//remove CR
			PID_Set_Params_Remote(MyOB1_ID, channel, reset,P,I);
		}
		

	} while (!(answer == "exit"));//stop if exit

	OB1_Destructor(MyOB1_ID);
	system("PAUSE");
	return 0;
}






