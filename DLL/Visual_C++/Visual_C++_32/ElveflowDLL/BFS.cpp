#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "MUX_DRI.h"
#include "dll/Elveflow32.h"//modify the additional include directory
using namespace std;

int main_BFS()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW errors.

	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "COM port hardcoded in the BFS.cpp file! ! ! FTDI driver required ! ! !" << endl;
	int  MyBFS_ID = -1;
	double data_temp = 0;
	double data_sens = 0;
	double data_dens = 0;
	//avoid non alphanumeric characters in device name
	error = BFS_Initialization("COM18", 0.001, 1, 1, &MyBFS_ID);//choose the com port, can be ASRLXXX::INSTR (where XXX=port number)
	Check_Error(error);//error sent if not recognized


	////////////////////////
	//
	// Main loop 
	//
	////////////////////////

	double value = 0;
	string answer_trigger = "";
	do {//loop until exit
		do {
			cout << "\n What to do (set_filter, do_zero, read_channel, or exit) : " << endl;
			getline(cin, answer);
		} while (!(answer == "set_filter" || answer == "do_zero" || answer == "read_channel" || answer == "exit"));

		if (answer == "set_filter")
		{
			double filter_value = 0;
			//ask the filter and set it
			cout << "set the filter (0.00001 = maximum filter, 1 = minimum filter)" << endl;
			cin >> filter_value;
			getline(cin, answer);//remove CR
			BFS_Set_Filter(MyBFS_ID, filter_value);
		}
		if (answer == "do_zero")//put valves before and after the BFS to stop the flow before performing zeroing
		{
			cout << "Zeroing last approximately 10 sec. Wait for the LED to stop blinking before sending an other command. \nRead corresponding User Guide to perform correctly the zeroing procedure." << endl;
			BFS_Zero(MyBFS_ID);
		}

		if (answer == "read_channel")
		{
			//get the density (!!!! NEED TO BE DONE AT LEAST ONCE BEFORE READING FLOW !!!!)

			cout << "Density: " << value << endl;
			BFS_Get_Data(MyBFS_ID, &data_sens, &data_temp, &data_dens);
			cout << "Sensor/Temperature/Density:" << data_sens << "," << data_temp << "," << data_dens << endl;

		}

	} while (!(answer == "exit"));//stop if exit
	BFS_Destructor(MyBFS_ID);
	system("PAUSE");
	return 0;
}

