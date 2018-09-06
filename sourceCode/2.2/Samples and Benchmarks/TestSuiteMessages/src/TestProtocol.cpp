#include "stdafx.h"
#include "TestProtocol.h"

#include "MessagesIDs.h"
#include "generated/messages.pb.h"



namespace testsuitemessages
{

TestProtocol::TestProtocol(void)
{
	registerMessage(LoginRequestID, &LoginRequest::default_instance());
	registerMessage(LoginResultResponseID, &LoginResultResponse::default_instance());
	registerMessage(EchoRequestID, &EchoRequest::default_instance());
	registerMessage(EchoResponseID, &EchoResponse::default_instance());
	registerMessage(RoutedMessageRequestID, &RoutedMessageRequest::default_instance());
	registerMessage(RoutedMessageResponseID, &RoutedMessageResponse::default_instance());
    registerMessage(GroupMessageRequestID, &GroupMessageRequest::default_instance());
    registerMessage(GroupMessageResponseID, &GroupMessageResponse::default_instance());
    registerMessage(BroadcastMessageRequestID, &BroadcastMessageRequest::default_instance());
    registerMessage(BroadcastMessageResponseID, &BroadcastMessageResponse::default_instance());
	registerMessage(SubscribeToBroadcastQueueRequestID, &SubscribeToBroadcastQueueRequest::default_instance());
	registerMessage(MemTestRequestID, &MemTestRequest::default_instance());
	registerMessage(MemTestResponseID, &MemTestResponse::default_instance());
}

TestProtocol::~TestProtocol(void)
{
}
}
