// stdafx.cpp : source file that includes just the standard includes
// TestSuiteClient.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <limits>

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
string fixedMessage = "";

void WaitForUserInput(const char* msg)
{
	while (true)
	{
		char ch;
		cout << msg << "Press 'c' to continue" << endl;

		cin >> ch;

		if (ch == 'c')
		{
			break;
		}
	}
}
