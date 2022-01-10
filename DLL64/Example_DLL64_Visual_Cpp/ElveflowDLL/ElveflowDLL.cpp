// Tested with Visual Studio 2015 (module C++)
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <Elveflow32.h>// modify the additional include directory

//add Elveflow.dll in the build directory
using namespace std;

void Check_Error(int ElveflowError)
{
	if (ElveflowError!=0)// uses Labview error code = > 0 = no error, else errors
	{
		cout << "error number " << ElveflowError << endl;
		system("PAUSE");
	}

};

int main()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;// use to obtain errors of function. If it's 0 -> no error , else -> error, see labview error 
	
	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "initiate the OB1 directelly in the cpp file" << endl;
	OB1_type *myOB1 = new OB1_type;
	// initialize the OB1 -> Use NiMAX to determine the device name
	//avoid non alphanumeric characters in device name
	error = OB1_Initialization("MyOB1", Regulator_type__0_2000_mbar,Regulator_type__0_2000_mbar, Regulator_type_m1000_1000_mbar, Regulator_type_m1000_1000_mbar, Sensor_type_Flow_1000_muL_min, Sensor_type_none, Sensor_type_none, Sensor_type_none, myOB1);
	Check_Error(error);// error send if not recognized
	
	////////////////////////
	//
	// Chose calibration
	//
	//////////////////////// 
	double *Calibration = new double[1000];// define the cailbration (array of double). Size can vary, depending on the instrument but 1000 is always enough
	do {//chose calibration
		cout << "Chose OB1 calibration: default , load , new" << endl;
		cin >> answer;
	} while (!(answer == "default" || answer == "load" || answer == "new"));
	
	//apply the desired calibration
	if (answer == "default")
	{
		Set_Default_Calib(Calibration,1000); //use default calibration
	}
	else if (answer == "load")
	{
		Elveflow_Calibration_Load("", Calibration,1000);// load the file contain in the path, if no path or non valid path, prompt ask the user to chose the file
	}
	else if (answer == "new")
	{
		cout << "wait ~2 minutes" << endl;
		OB1_Calib(myOB1, Calibration, 1000);//Perform calibration ! ! ! Take about 2 minutes ! ! !
		error = Elveflow_Calibration_Save("", Calibration,1000); // Save calibration in the selected path, if no path or path non valid, open prompt to ask the file name
		Check_Error(error);
	}
	
	
	////////////////////////
	//
	// Main loop 
	//
	////////////////////////
	int channel = 0;
	double set_pressure = 0;
	double* get_pressure = new double[4];
	double get_flow = 0;
	int trigger = 0;
	string answer_trigger = "";
	do {// loop until exit
		do {
			cout << "Chose what to do: get pressure, set pressure, get sensor, set trigger, get trigger or exit" << endl;
			getline(cin, answer);
		} while (!(answer == "get pressure" || answer == "set pressure" || answer == "get sensor" || answer == "get trigger"|| answer == "set trigger" || answer == "exit"));

		if (answer == "get pressure") 
		{
			//read pressure of 4 channels
			OB1_Get_Press(myOB1, 1000, Calibration, get_pressure, 1000, 4);
			for (int i = 0; i < 4; i++)
			{
				cout << "channel " << i << ": " << get_pressure[i] << " mbar" << endl;
			}
		}

		if (answer == "set pressure")
		{
			//ask the target pressure and the channel, and set the value
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			cout << "value (mbar)" << endl;
			cin >> set_pressure;
			OB1_Set_Press(myOB1, channel, set_pressure, Calibration, 1000);
		}
		if (answer == "get sensor")
		{
			//ask the channel, and read the value
			cout << "channel (1 to 4)?" << endl;
			cin >> channel;
			OB1_Get_Flow(myOB1, channel, &get_flow);//use pointer 
			cout << "channel " << channel << ": " << get_flow << " µl/min" << endl;
		}
		if (answer == "set trigger")
		{
			//ask the target pressure and the channel, and set the value
			do
			{
				cout << "new value (high or low)" << endl;
				getline(cin, answer_trigger);
			} while (!(answer_trigger == "high" || answer_trigger == "low"));
			if (answer_trigger == "high")
			{
				OB1_Set_Trigger(myOB1, 1);
			}
			else
			{
				OB1_Set_Trigger(myOB1, 0);
			}
		}
		if (answer == "get trigger")
		{
			string trigger_string="";
			OB1_Get_Trigger(myOB1, &trigger);
			if (trigger == 0) trigger_string = "low";
			else trigger_string = "high";
			cout << "trigger is " << trigger_string << endl;

		}

	} while (!(answer == "exit"));//stop if exit

	system("PAUSE");
    return 0;
}

