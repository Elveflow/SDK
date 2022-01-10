#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "F_SReader.h"
#include <Elveflow64.h> //modify the additional include directory
using namespace std;

int main_F_SReader()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW errors.

	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "device name and sensor hardcoded in the F_SReader.cpp file" << endl;

	int  MyF_S_Reader_ID = -1;

	//initialize the F_S_Reader -> Use NIMAX to determine the device name
	//avoid non alphanumeric characters in device name
	error = F_S_R_Initialization("MySensorReader", Z_sensor_type_Flow_1000_muL_min, Z_sensor_type_none, Z_sensor_type_Press_340_mbar, Z_sensor_type_none, &MyF_S_Reader_ID);//remember that sensors 1-2 and 2-3 should be the same kind
	Check_Error(error);//error sent if not recognized

	////////////////////////
	//
	// Main loop 
	//
	////////////////////////

	double get_output = 0;
	int channel = 0;

	do {
		cout << "\nChoose the channel to check: 1-4 (other number = exit)" << endl;
		cin >> channel;
		if (channel > 0 && channel<5)
		{
			error= F_S_R_Get_Sensor_data(MyF_S_Reader_ID, channel, &get_output);//remember pointer for output
			Check_Error(error);
			cout << "read value: " << get_output << endl;
		}
		else 
		{ channel = 0; }//reset channel to 0
		getline(cin, answer);

	} while ((channel > 0 && channel < 5));

	F_S_R_Destructor(MyF_S_Reader_ID);//close communication with flow sensor
	system("PAUSE");
	return 0;
}
