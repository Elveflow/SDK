#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "error_check.h"
using namespace std;

//function used to check error from functions, it uses LabVIEW errors that could be ckecked on internet

void Check_Error(int ElveflowError)
{
	if (ElveflowError != 0)
	{
		cout << "error number " << ElveflowError << endl;
		system("PAUSE");
	}

};