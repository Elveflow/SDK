#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "M_S_R_D.h"
#include <Elveflow32.h>//modify the additional include directory
using namespace std;

int main_M_S_R_D()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW errors.

	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "device name and sensor hardcoded in the M_S_R_D.cpp file" << endl;

	int  MyM_S_R_D_ID = -1;

	//initialize the M_S_R_D -> Use NIMAX to determine the device name
	//avoid non alphanumeric characters in device name
	error = M_S_R_D_Initialization("01EE3A1A",5,0,0,0,0,0,&MyM_S_R_D_ID);//remember that sensors 1-2 and 3-4 should be the same kind //the sensors types have to be the same as in the next function "Add_Sens" (CustomSens_Voltage_Ch12 and Ch34 is used for CustomSensors only, voltage is between 5 and 25V)
	Check_Error(error);//error sent if sensors not compatible together

	//add a sensor depending on the sensor connected (see SDK User Guide to add properly the sensor depending on its type)
	error = M_S_R_D_Add_Sens(MyM_S_R_D_ID,1,5,1,0,7);//add digital flow sensor on channel 1 with H2O Calibration and 16 bits resolution
	// ! ! ! If the sensor is not recognized a pop up will indicate it

	//error = M_S_R_D_Set_Filt(MyM_S_R_D_ID, 1, true); //to set analog filter on channel 1

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
			error = M_S_R_D_Get_Sens_Data(MyM_S_R_D_ID, channel, &get_output);//remember pointer for output
			Check_Error(error);
			cout << "read value: " << get_output << endl;
		}
		else
		{
			channel = 0;
		}//reset channel to 0
		getline(cin, answer);

	} while ((channel > 0 && channel < 5));

	M_S_R_D_Destructor(MyM_S_R_D_ID);//close communication with flow sensor
	system("PAUSE");
	return 0;
}
