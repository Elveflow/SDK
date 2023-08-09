#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "MUX_DRI.h"
#include "dll/Elveflow64.h"
//#include <Elveflow64.h>//modify the additional include directory
using namespace std;

int main_MUX_DRI()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW error.

	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "COM port hardcoded in the MUX_DRI.cpp file/n! ! ! FTDI driver required ! ! !" << endl;
	int  MyMUX_DRI_ID = -1;
	//initialize the MUX Distribution, Distributor, Recirculation or Injection -> Use NIMAX to determine the device name
	//avoid non alphanumeric characters in device name
	error = MUX_DRI_Initialization("ASRL11::INSTR", &MyMUX_DRI_ID);//Choose the com port, it can be ASRLXXX::INSTR (where XXX=port number)
	Check_Error(error);//error sent if not recognized

	char* Answer = new char[40];//define the answer (array of char). Size can vary, depending on the action asked but 40 is enough.

	////////////////////////
	//
	// Main loop 
	//
	////////////////////////

	int valve = -1;
	string answer_trigger = "";
	do {//loop until exit
		do {
			cout << "\nChoose what to do: get valve, set valve, home valve, get serial number or exit" << endl;
			getline(cin, answer);
		} while (!(answer == "get valve" || answer == "set valve" || answer == "home valve" || answer == "get serial number" || answer == "exit"));

		if (answer == "get valve")
		{
			//get the active valve. it returns 0 if valve is busy.
			MUX_DRI_Get_Valve(MyMUX_DRI_ID, &valve);
			cout << "active valve: " << valve << endl;
		}

		if (answer == "set valve")
		{
			//set the desired valve
			//you can select valve rotation way, either shortest, clockwise or counter clockwise (only for MUX Distribution and Recirculation)
			cout << "select valve" << endl;
			cin >> valve;
			getline(cin, answer);//remove CR
			MUX_DRI_Set_Valve(MyMUX_DRI_ID, valve, Z_MUX_DRI_Rotation_Shortest);
		}

		if (answer == "home valve")
		{
			//send the command to Home the valve (only for MUX Distribution and Recirculation)
			//Home the valve can take several seconds. Wait for the end of the valve movement to be able to set a new valve position.
			MUX_DRI_Send_Command(MyMUX_DRI_ID, Z_MUX_DRI_Action_Home, Answer, 40); //set 40 for the length
			cout << "Answer: " << Answer << endl;
		}

		if (answer == "get serial number")
		{
			//send the command to get the Serial Number (only for MUX Distribution and Recirculation)
			MUX_DRI_Send_Command(MyMUX_DRI_ID, Z_MUX_DRI_Action_SerialNumber, Answer, 40); //set 40 for the length
			cout << "Answer: " << Answer << endl;
		}

	} while (!(answer == "exit"));//stop if exit
	MUX_DRI_Destructor(MyMUX_DRI_ID);
	system("PAUSE");
	return 0;
}

