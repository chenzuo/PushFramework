/********************************************************************
	File :			ChannelFactory.cpp
	Creation date :	2010/6/27

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.


*********************************************************************/
#include "StdAfx.h"
#include "ChannelFactory.h"

#include "ServerImpl.h"

#ifdef Plateform_Windows
#include "IOQueue_Win.h"
#else
#ifdef Plateform_Linux
#include "IOQueue_Linux.h"
#endif
#endif

#include "Dispatcher.h"
#include "Listener.h"
#include "ScopedLock.h"
#include "ClientFactoryImpl.h"
#include "../include/ServerOptions.h"


namespace PushFramework
{

ChannelFactory channelFactory;

ChannelFactory::ChannelFactory()
{
    ::InitializeCriticalSection(&csChannelMap);
    isPermitOnly = false;
}

ChannelFactory::~ChannelFactory(void)
{
    ::DeleteCriticalSection(&csChannelMap);
}

bool ChannelFactory::isAddressAllowed( IN_ADDR SockAddr )
{
    long ip = SockAddr.s_addr;

    ipRangeListT& list = isPermitOnly ? permittedIPs : blockedIPs;
    bool bIsInList = false;


	for (ipRangeListT::iterator it = list.begin();
		it!= list.end();
		it++)
    {
        IPRange& ipRange = *it;

        long start = ipRange.startIP.s_addr;
        long stop = ipRange.endIP.s_addr;

        if (ip <= stop && ip >= start)
        {
            bIsInList = true;
            break;
        }
    }
    return isPermitOnly ? bIsInList : !bIsInList;
}

void ChannelFactory::addIPRangeAccess( const char* ipStart, const char* ipStop, bool bPermit )
{
    isPermitOnly = bPermit;

    IPRange ipRange;

    ipRange.startIP.s_addr = inet_addr(ipStart);
    ipRange.endIP.s_addr = inet_addr(ipStop);

    ipRangeListT& list = bPermit ? permittedIPs : blockedIPs;

    list.push_back(ipRange);
}

bool ChannelFactory::removePhysicalConnection( PhysicalConnection* pChannel )
{
    ScopedLock lock(csChannelMap);

    vectConnectionsT::iterator it = vectPendingPhysicalConnections.begin();

    while (it != vectPendingPhysicalConnections.end())
    {
        if ((*it) == pChannel)
        {
            vectPendingPhysicalConnections.erase(it);
            return true;
        }
        it ++;
    }

    return false;
}

void ChannelFactory::scrutinize()
{
    ScopedLock lock(csChannelMap);

    vectConnectionsT::iterator it = vectPendingPhysicalConnections.begin();

    while (it != vectPendingPhysicalConnections.end())
    {
        PhysicalConnection* pChannel = *it;

		if (pChannel->getStatus() == PhysicalConnection::Connected)
		{
			// Verify expiry : 
			int nMaxDuration = pChannel->isObserverChannel() ? 40 : options.uLoginExpireDuration;
			if (pChannel->getLifeDuration() > nMaxDuration)
			{
				pChannel->closeConnection(false);
			}
		}

		// Delete disposable pending connections :
		if (pChannel->checkIfUnusedByIOWorkers())
		{
			disposePhysicalConnection(pChannel);

			it = vectPendingPhysicalConnections.erase(it);
		}
		else{			
			it++;
		}        
    }
}

void ChannelFactory::stop()
{
    //Remove all connections (Demux is already stopped):
    vectConnectionsT::iterator it = vectPendingPhysicalConnections.begin();
    while (it != vectPendingPhysicalConnections.end())
    {
        PhysicalConnection* pChannel = *it;
        disposePhysicalConnection(pChannel);
        it = vectPendingPhysicalConnections.erase(it);
    }
}

void ChannelFactory::addPhysicalConnection( PhysicalConnection* pChannel )
{
	ScopedLock lock(csChannelMap);

	vectPendingPhysicalConnections.push_back(pChannel);
}

void ChannelFactory::disposePhysicalConnection( PhysicalConnection* pChannel )
{
	if(options.usePools)
		deleteObject(pChannel);
	else
		delete pChannel;
}

void ChannelFactory::start()
{
	if (options.usePools){
		initialize(options.nPhysicalConnectionsPoolSize);
	}
}

}
