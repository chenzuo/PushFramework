// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

#include <PushFrameworkInc.h>
using namespace PushFramework;


#include <google/protobuf/stubs/common.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
using namespace google;


#include <TestSuiteMessagesInc.h>
using namespace testsuitemessages;

#include <TCPSocketInclude.h>

void WaitForUserInput(const char* msg);

#include "ConsoleColor.h"

extern string fixedMessage;