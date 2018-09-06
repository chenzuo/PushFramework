// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "Plateform.h"

#ifdef Plateform_Windows
#include "targetver.h"
#include <Windows.h>
#endif

#include <stdio.h>

#include <ctype.h>
#include <iostream>
#include <fstream>

#include <string.h>

#include <string>
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

#include "generated/messages.pb.h"
using namespace messages;

bool BroadcastPacket(protobuf::Message* pMessage, BROADCASTQUEUE_NAME channelName);
bool BroadcastPacket(protobuf::Message* pMessage, BROADCASTQUEUE_NAME channelName, BROADCASTPACKET_KEY killKey, int objectCategory);
