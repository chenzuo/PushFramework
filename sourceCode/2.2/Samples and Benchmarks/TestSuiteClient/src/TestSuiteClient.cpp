// TestSuiteClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestClient.h"
#include "BasicWorkflowsTest.h"
#include "QoSTest.h"
#include "MemTest.h"

void CreateTests();
void ClearTests();
void PrintTests();
bool SelectTestAndRun();

vector<TestSuiteBase*> testsList;

void CreateTests()
{
    testsList.push_back(new CBasicWorkflowsTest);
	testsList.push_back(new CQoSTest);
	testsList.push_back(new CMemTest);
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i=0;i<1024;i++)
		fixedMessage += "a";

	//system("Color 1A");
	TCPSocket::initializeWinsock();

    CreateTests();
    
    while (true)
    {
        PrintTests();
        if (!SelectTestAndRun())
        {
            break;
        }
    }

    ClearTests();

	return 0;
}

void PrintTests()
{
    std::system ( "CLS" );
    cout << "******* Select from list of tests: *********" << endl;
    for (int i=0;i<testsList.size();i++)
    {
        cout << (i+1) << ": " << testsList.at(i)->GetTitle() << endl;
    }
    cout << "*******" << endl;
}
bool SelectTestAndRun()
{
    char ch;
    cin >> ch;

    if (!isdigit(ch))
        return false;


    int iTest = atoi (&ch) - 1;

    if (iTest >= testsList.size())
    {
        cout << "Wrong index" << endl;
        return true;
    }

    TestSuiteBase* pTest = testsList.at(iTest);

    std::system ( "CLS" );
    cout << green << "Running test: " << pTest->GetTitle() << white << endl;
    cout << "Description: " << endl;
    cout << "\t\t" << pTest->GetDescription() << endl;


    pTest->DoTest();


    cout << green << "Test is completed" << white << endl;
    
    WaitForUserInput("");

    return true;
}
void ClearTests()
{
    for (int i= 0;i<testsList.size();i++)
    {
        delete testsList.at(i);
    }
}

