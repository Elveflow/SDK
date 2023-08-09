#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "MUX_DRI.h"
//#include <Elveflow64.h>//modify the additional include directory
#include "dll/Elveflow64.h"
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
	cout << "COM port hardcoded in the BFS.cpp file/n! ! ! FTDI driver required ! ! !" << endl;
	int  MyBFS_ID = -1;
	//avoid non alphanumeric characters in device name
	error = BFS_Initialization("ASRL14::INSTR", &MyBFS_ID);//Choose the com port, it can be ASRLXXX::INSTR (where XXX=port number)
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
			cout << "\nChoose what to do: get density, get flow, get temperature, set filter, do zero or exit" << endl;
			getline(cin, answer);
		} while (!(answer == "get density" || answer == "get flow" || answer == "get temperature" || answer == "set filter" || answer == "do zero" || answer == "exit"));

		if (answer == "get density")
		{
			//get the density (!!!! NEED TO BE DONE AT LEAST ONCE BEFORE READING FLOW !!!!)
			BFS_Get_Density(MyBFS_ID, &value);
			cout << "Density: " << value << endl;
		}
		if (answer == "get flow")
		{
			//get the flow (!!!! NEED TO measure density at least one time before using this function, density is used to measure the flux !!!!)
			BFS_Get_Flow(MyBFS_ID, &value);
			cout << "flow: " << value << endl;
			cout << "Remember that density need to be measured at least once before using this function since density is used to measure the flow. If measurement frequency is not critical, always measure first density and then flow" << endl;
		}
		if (answer == "get temperature")
		{
			//get the temperature
			BFS_Get_Temperature(MyBFS_ID, &value);
			cout << "Temperature: " << value << endl;
			
		}
		if (answer == "set filter")
		{
			double filter_value = 0;
			//ask the filter and set it
			cout << "set the filter (0.00001 = maximum filter, 1 = minimum filter)" << endl;
			cin >> filter_value;
			getline(cin, answer);//remove CR
			BFS_Set_Filter(MyBFS_ID, filter_value);
		}
		if (answer == "do zero")//put valves before and after the BFS to stop the flow before performing zeroing
		{
			cout << "Zeroing last approximately 10 sec. Wait for the LED to stop blinking before sending an other command. \nRead corresponding User Guide to perform correctly the zeroing procedure." << endl;
			BFS_Zeroing(MyBFS_ID);
		}

	} while (!(answer == "exit"));//stop if exit
	BFS_Destructor(MyBFS_ID);
	system("PAUSE");
	return 0;
}

