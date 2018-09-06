#include "StdAfx.h"
#include "DirectChatRequestService.h"

#include "ChatParticipant.h"


DirectChatRequestService::DirectChatRequestService(void)
{

}

DirectChatRequestService::~DirectChatRequestService(void)
{
}

void DirectChatRequestService::handle( LogicalConnection* pClient, IncomingPacket* pRequest )
{
    ChatParticipant* pParticipant = (ChatParticipant*) pClient;

    DirectChatRequest* request = (DirectChatRequest*) pRequest;

    ChatParticipant* pRecipient = (ChatParticipant*) FindClient(request->Recipient().c_str());
    if (pRecipient)
    {
        DirectChatResponse ChatResponse;
        ChatResponse.Sender(pParticipant->getKey());
        ChatResponse.Msg(request->Msg());

        pRecipient->PushPacket(&ChatResponse);

        ReturnClient(pRecipient);
    }
}
