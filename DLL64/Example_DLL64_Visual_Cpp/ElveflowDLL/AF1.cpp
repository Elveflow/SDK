#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "AF1.h"
#include <Elveflow64.h> //modify the additional include directory

using namespace std;

int main_AF1()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW errors.
	
	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "device name, regulator and sensor hardcoded in the AF1.cpp file" << endl;
	int  MyAF1_ID = -1;
	//initialize the AF1 -> Use NIMAX to determine the device name
	//avoid non alphanumeric characters in device name
	//error = AF1_Initialization("MyAF1", Z_regulator_type_m1000_1000_mbar,Z_sensor_type_Flow_1000_muL_min, &MyAF1_ID);
	error = AF1_Initialization("Dev15", 2, Z_sensor_type_Flow_1000_muL_min, &MyAF1_ID);
	Check_Error(error);//error sent if not recognized
	
	////////////////////////
	//
	// Choose calibration
	//
	//////////////////////// 

	double *Calibration = new double[1000];//define the calibration (array of double). Size can vary, depending on the instrument but 1000 is always enough.
	do {//choose calibration
		cout << "Choose AF1 calibration: default , load , new" << endl;
		getline(cin, answer);
	} while (!(answer == "default" || answer == "load" || answer == "new"));
	
	//apply the desired calibration
	if (answer == "default")
	{
		Elveflow_Calibration_Default(Calibration,1000); //use default calibration
	}
	else if (answer == "load")
	{
		Elveflow_Calibration_Load("", Calibration,1000);//load the file contained in the path, if no path or non valid path, prompt ask the user to choose the file
	}
	else if (answer == "new")
	{
		cout << "wait ~2 minutes" << endl;
		AF1_Calib(MyAF1_ID, Calibration, 1000);//Perform calibration ! ! ! Take about 2 minutes ! ! !
		error = Elveflow_Calibration_Save("", Calibration,1000); //save calibration in the selected path, if no path or path non valid, open prompt to ask the file name
		Check_Error(error);
	}
	
	
	////////////////////////
	//
	// Main loop 
	//
	////////////////////////

	double set_pressure = 0;
	double get_pressure=0;
	double get_flow = 0;
	int trigger = 0;
	string answer_trigger = "";
	do {//loop until exit
		do {
			cout << "\nChoose what to do: get pressure, set pressure, get sensor, set trigger, get trigger or exit" << endl;
			getline(cin, answer);
		} while (!(answer == "get pressure" || answer == "set pressure" || answer == "get sensor" || answer == "get trigger"|| answer == "set trigger" || answer == "exit"));

		if (answer == "get pressure") 
		{
			//read pressure of 4 channels
			AF1_Get_Press(MyAF1_ID, 1000, Calibration, &get_pressure, 1000);//pass pointer to get_pressure in order to modify its value
			cout << "pressure: " << get_pressure << " mbar" << endl;
		}

		if (answer == "set pressure")
		{
			//ask the target pressure and set the value
			cout << "value (mbar)" << endl;
			cin >> set_pressure;
			getline(cin, answer);//remove CR
			AF1_Set_Press(MyAF1_ID, set_pressure, Calibration, 1000);
		}
		if (answer == "get sensor")
		{
			//read sensor value
			AF1_Get_Flow_rate(MyAF1_ID, &get_flow);//use pointer 
			cout << " flow : " << get_flow << " µl/min" << endl;//return 0 if no sensor
		}
		if (answer == "set trigger")
		{
			do
			{
				cout << "new value (high or low)" << endl;
				getline(cin, answer_trigger);
			} while (!(answer_trigger == "high" || answer_trigger == "low"));
			if (answer_trigger == "high")
			{
				AF1_Set_Trig(MyAF1_ID, 1);
			}
			else
			{
				AF1_Set_Trig(MyAF1_ID, 0);
			}
		}
		if (answer == "get trigger")
		{
			string trigger_string="";
			AF1_Get_Trig(MyAF1_ID, &trigger);
			if (trigger == 0) trigger_string = "low";
			else trigger_string = "high";
			cout << "trigger is " << trigger_string << endl;

		}

	} while (!(answer == "exit"));//stop if exit
	AF1_Destructor(MyAF1_ID);
	system("PAUSE");
    return 0;
}

