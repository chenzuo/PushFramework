#include "StdAfx.h"
#include "BasicWorkflowsTest.h"

CBasicWorkflowsTest::CBasicWorkflowsTest(void)
{
}

CBasicWorkflowsTest::~CBasicWorkflowsTest(void)
{
}

void CBasicWorkflowsTest::PrepareConnections()
{
    client1.ConnectToServer("C1");
    client2.ConnectToServer("C2");
    client3.ConnectToServer("C3");

    client1.WaitForLogin();
    client2.WaitForLogin();
    client3.WaitForLogin();
}

void CBasicWorkflowsTest::DoTest()
{
    PrepareConnections();
    
    cout << "Testing Echo.." << endl;
    TestEcho();

    cout << "Testing Routed Communication.." << endl;
    TestRoutedCommunication();

    cout << "Testing Group Communication.." << endl;
    TestGroupCommunication();
}

const char* CBasicWorkflowsTest::GetTitle()
{
    return "Basic Tests";
}

const char* CBasicWorkflowsTest::GetDescription()
{
    return "Performs tests of basic communications workflows";
}

void CBasicWorkflowsTest::TestEcho()
{
    EchoRequest request;
    request.set_msg("Hello World!");

    client1.sendRequest(&request);
    
    Sleep(1000);
}

void CBasicWorkflowsTest::TestRoutedCommunication()
{
    RoutedMessageRequest request;

    request.set_msg("Hello");
    request.set_recipient("C2");

    client1.sendRequest(&request);
    Sleep(1000);
}

void CBasicWorkflowsTest::TestGroupCommunication()
{
    GroupMessageRequest request;

    request.set_msg("Hello");

    client1.sendRequest(&request);
    Sleep(1000);
}
