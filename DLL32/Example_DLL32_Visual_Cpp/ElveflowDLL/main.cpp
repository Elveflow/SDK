// Tested with Visual Studio 2019 (module C++)
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "OB1.h"
#include "AF1.h"
#include "F_SReader.h"
#include "MUX_DRI.h"
#include "MUX.h"
#include "BFS.h"
#include "M_S_R_D.h"
#include <Elveflow32.h>// modify the additional include directory


//add Elveflow.dll in the build directory
using namespace std;

int main()
{
	//this function only select instrument and then used OB1_main, AF1_main, FSR_main, MUX_main, or MUX_DRI_main
	string instrument_type = ""; //create a new variable to store the user answer for communication
	
	////////////////////////
	//
	// Initialization
	//
	//! ! !  if an instrument was not properly close, it may cause an error ! ! !
	//
	////////////////////////
	do {
		cout << "select instrument: OB1, AF1, F_S_R (for Flow Reader or Sensor Reader), M_S_R_D (for Sensor Reader able to read digital sensors), MUX, MUX DRI (for MUX Distribution, Distributor, Recirculation or Injection), BFS (for Bronkhorst Mini-cori-Flow)" << endl;
		getline(cin, instrument_type);
	} while (!(instrument_type == "OB1" || instrument_type == "AF1" || instrument_type == "F_S_R" || instrument_type == "M_S_R_D" || instrument_type == "MUX" || instrument_type == "MUX DRI"||instrument_type == "BFS"));
	if (instrument_type == "OB1")
	{
		main_OB1();
	}
	else if (instrument_type == "AF1")
	{
		main_AF1();
	}
	else if (instrument_type == "F_S_R")
	{
		main_F_SReader();
	}
	else if (instrument_type == "M_S_R_D")
	{
		main_M_S_R_D();
	}
	else if (instrument_type == "MUX")
	{
		main_MUX();
	}
	else if (instrument_type == "MUX DRI")
	{
		main_MUX_DRI();
	}
	else if (instrument_type == "BFS")
	{
		main_BFS();
	}
    return 0;
}

