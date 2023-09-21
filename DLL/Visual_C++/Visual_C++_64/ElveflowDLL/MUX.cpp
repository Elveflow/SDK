#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "error_check.h"
#include "MUX.h"
#include "dll/Elveflow64.h"

using namespace std;

int main_MUX()
{
	string answer = "a"; //create a new variable to store the user answer for communication
	int error = 0;//used to obtain errors of functions. If it's 0 -> no error , else -> error, see LabVIEW errors.
	
	////////////////////////
	//
	// Initialization
	//
	////////////////////////
	cout << "device name hardcoded in the MUX.cpp file" << endl;
	int  MyMUX_ID = -1;
	//initialize the MUX -> Use NIMAX to determine the device name
	//avoid non alphanumeric characters in device name
	error = MUX_Initialization("COM9", &MyMUX_ID);//choose instrument port
	Check_Error(error);//error sent if not recognized
	
	
	////////////////////////
	//
	// Main loop 
	//
	////////////////////////

	int input_valve = -1;
	int output_valve = -1;
	int valve_state = -1;
	int all_valves[16] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };//init all valves here !!! should be exactly 16 elements, otherwise nothing will happen
	int all_valves_close[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//all valves closed
	int all_valves_open[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };//all valves opened
	int trigger = -1;
	int* TypesArray = new int[8];
	string answer_trigger = "";
	string answer_ValveNumber = "";
	int valveNB = 0;
	string type_string = "";
	string answer_ValveType = "";

	do {//loop until exit
		do {
			cout << "\nChoose what to do: set individual valve, set all valves, close all, open all, set valves(Wire), get trigger, Get Type, Set Type, set trigger op exit" << endl;
			getline(cin, answer);
		} while (!(answer == "set individual valve" || answer == "set all valves" || answer=="set valves(Wire)"||answer == "get trigger" || answer == "open all" || answer == "close all" || answer == "set trigger" || answer == "exit" || answer == "Set Type" || answer == "Get Type"));

		if (answer == "set individual valve")
		{
			//get the active valve (for mux quake only)
			cout << "input valve" << endl;
			cin >> input_valve;
			cout << "output valve" << endl;
			cin >> output_valve;
			cout << "valve state (0=Close, 1=open)" << endl;
			cin >> valve_state;
			getline(cin, answer);
			MUX_Set_indiv_valve(MyMUX_ID, input_valve, output_valve, valve_state);
		}

		if (answer == "set valves(Wire)")
		{

			//set all the valves for MUX Wire
			cout << "valve state hard coded in the MUX.cpp file" << endl;
			MUX_Wire_Set_all_valves(MyMUX_ID, all_valves, 16);//set the valves of the MUX WIRE ! The encoding is not the same for other MUX.
		}
		
		if (answer == "Get Type")
		{

			//Get valve type for MUX Wire V3 version

			
			do
			{
				cout << "choose the valve number (1 to 8)" << endl;
				getline(cin, answer_ValveNumber);
			} while (!(answer_ValveNumber == "1" || answer_ValveNumber == "2" || answer_ValveNumber == "3" || answer_ValveNumber == "4" || answer_ValveNumber == "5" || answer_ValveNumber == "6" || answer_ValveNumber == "7" || answer_ValveNumber == "8"));
			
			MUX_Get_valves_Type(MyMUX_ID, TypesArray, 8);
			valveNB = stoi(answer_ValveNumber)-1;
			

			if (TypesArray[valveNB] == 0)
			{
				type_string = "Empty";
			}
			
			else if (TypesArray[valveNB] == 1)
			{
				type_string = "NC V3";
			}
			else if (TypesArray[valveNB] == 2)
			{
				type_string = "NO V3";
			}
			else if (TypesArray[valveNB] == 3)
			{
				type_string = "UNIVERSAL V3";
			}
			else if (TypesArray[valveNB] == 4)
			{
				type_string = "NC Custom";
			}
			else if (TypesArray[valveNB] == 5)
			{
				type_string = "NO Custom";
			}
			else
			{
				type_string = "UNIVERSAL Custom";
			}

			cout << "Valve " << answer_ValveNumber << " is " << type_string << endl;
		
		}
		
		if (answer == "Set Type")
		{

			//Set valve type for MUX Wire V3 version
			do
			{
				cout << "choose the valve number (1 to 8)" << endl;
				getline(cin, answer_ValveNumber);
			} while (!(answer_ValveNumber == "1" || answer_ValveNumber == "2" || answer_ValveNumber == "3" || answer_ValveNumber == "4" || answer_ValveNumber == "5" || answer_ValveNumber == "6" || answer_ValveNumber == "7" || answer_ValveNumber == "8"));
			valveNB = stoi(answer_ValveNumber);
			do
			{
				cout << "choose valve type you want (Undefined,NC, NO or Universal)" << endl;
				getline(cin, answer_ValveType);
			} while (!(answer_ValveType == "Universal" || answer_ValveType == "NC" || answer_ValveType == "NO" || answer_ValveType == "Undefined"));

			
			if (answer_ValveType == "Universal")
			{
				MUX_Set_valves_Type(MyMUX_ID, valveNB, Enum__32UniversalCustom);
			}
			else if (answer_ValveType == "NC")
			{
				MUX_Set_valves_Type(MyMUX_ID, valveNB, Enum__22NormallyClosedCustom);
			}
			else if (answer_ValveType == "Undefined")
			{
				MUX_Set_valves_Type(MyMUX_ID, valveNB, Enum_UNDEFINED);
			}
			else
			{
				MUX_Set_valves_Type(MyMUX_ID, valveNB, Enum__22NormallyOpenedCustom);
			}
			
		}
		
		if (answer == "set valves(Wire)")
		{

			//set all the valves for MUX Wire
			cout << "valve state hard coded in the MUX.cpp file" << endl;
			MUX_Wire_Set_all_valves(MyMUX_ID, all_valves, 16);//set the valves of the MUX WIRE ! The encoding is not the same for other MUX.
		}

		if (answer == "set all valves")
		{

			//set all the valves for MUX different from MUX Wire
			cout << "valve state hard coded in the MUX.cpp file" << endl;
			MUX_Set_all_valves(MyMUX_ID, all_valves, 16);// 
		}

		if (answer == "close all")
		{
			cout << "all valves closed" << endl;
			MUX_Set_all_valves(MyMUX_ID, all_valves_close, 16);// 
		}
		if (answer == "open all")
		{
			cout << "all valves opened" << endl;
			MUX_Set_all_valves(MyMUX_ID, all_valves_open, 16);// 
		}
		if (answer == "set trigger")
		{
			//set the trigger
			do
			{
				cout << "new value (high or low)" << endl;
				getline(cin, answer_trigger);
			} while (!(answer_trigger == "high" || answer_trigger == "low"));
			if (answer_trigger == "high")
			{
				MUX_Set_Trig(MyMUX_ID, 1);
			}
			else
			{
				MUX_Set_Trig(MyMUX_ID, 0);
			}
		}
		if (answer == "get trigger")
		{
			string trigger_string = "";
			MUX_Get_Trig(MyMUX_ID, &trigger);
			if (trigger == 0) trigger_string = "low";
			else trigger_string = "high";
			cout << "trigger is " << trigger_string << endl;

		}
		
	} while (!(answer == "exit"));//stop if exit
	MUX_Destructor(MyMUX_ID);
	system("PAUSE");
    return 0;
}

