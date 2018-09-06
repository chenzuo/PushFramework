
#include "StdAfx.h"
#include "ChannelFactory.h"
#include "ServerImpl.h"
#include "Dispatcher.h"
#include "../include/ServerOptions.h"


#ifdef Plateform_Windows
#include "IOQueue_Win.h"
#else
#ifdef Plateform_Linux
#include "IOQueue_Linux.h"
#endif
#endif

namespace PushFramework
{

bool ChannelFactory::createPhysicalConnection( SOCKET hSocket, SOCKADDR_IN address, bool isObserver )
{
    PhysicalConnection* pChannel;

    if (options.usePools){
		pChannel = createObject();
		if (!pChannel)
		{
			return false;
		}
	}
    else
            pChannel = new PhysicalConnection();
    // In both cases reset the object.
    pChannel->reset(hSocket, address, isObserver);

    addPhysicalConnection(pChannel);

    //Now Associate with IOCP main Handle
    if (!ioQueue.addSocketContext(hSocket, pChannel))
    {
        removePhysicalConnection(pChannel);
        delete pChannel;
        //leave socket close to acceptor
        return false;
    }
 
    dispatcher.handleInitialize(pChannel);
    return true;
}
}
