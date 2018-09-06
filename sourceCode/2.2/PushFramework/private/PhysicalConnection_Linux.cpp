/********************************************************************
	File :			PhysicalConnection_Linux.cpp
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
#include "PhysicalConnection.h"

#include "ScopedLock.h"
#include "ServerImpl.h"
#include "ServerStats.h"
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

void PhysicalConnection::postReceive()
{
	if (status < Connected)
	{
		return;
	}

    // Rearm the socket for next read event:
	if(ioQueue.rearmSocketForRead(getSocket(), this))
	{
		incrementIoWorkersReferenceCounter();
	}
}

bool PhysicalConnection::readReceivedBytes(int& dwIoSize)
{
	// In Linux we only know bytes untill we issue a read.
    dwIoSize = 0;
    
    while (true)
    {
        int nMaxToPick = min(options.uReadBufferSize, inBuffer.getRemainingSize());
        if(nMaxToPick == 0){
            // This should be an impossible case.
			return false;            
        }
        
		int ret = recv(socket, inBuffer.getBuffer() + inBuffer.getDataSize(), nMaxToPick, 0);
		if (ret == 0)
		{
			// Peer closed the connection. Will be handled by caller.
			return false;
		}

		if (ret < 0)
		{
			if (errno != EAGAIN)
			{
				// IO failure. Close the connection.
				return false;
			}
			break;
		}

        dwIoSize += ret;
        dtLastReceiveTime = time(NULL);
        inBuffer.growSize(ret);
    }

	// Report bytes read to stats object.
	if (!isObserverChannel())
	{
		stats.addToCumul(ServerStats::BandwidthInbound, dwIoSize);
		stats.addToKeyedDuration(ServerStats::BandwidthInboundPerConnection, this->getSocket(), dwIoSize);
	}

    return true;
}

bool PhysicalConnection::WriteBytes()
{
    //We should call send, until the return value is EAGAIN
    while (true)
    {
        int dwToPick = min(options.uSendBufferSize, oBuffer.getDataSize());
        if (dwToPick == 0)
            return true;

        int ret = send(socket, oBuffer.getBuffer(), dwToPick, 0);

        if (ret > 0)
        {
            oBuffer.pop(ret);
            bool reportSentData = !isObserverChannel();

            if (reportSentData)
            {
                stats.addToCumul(ServerStats::BandwidthOutbound, ret);
                stats.addToKeyedDuration(ServerStats::BandwidthOutboundPerConnection, this->getSocket(), ret);
            }
        }
        else if (errno == EAGAIN)
        {
            bWriteInProgress = TRUE;
            this->incrementIoWorkersReferenceCounter();
            ioQueue.rearmSocketforWrite(getSocket(), this);
            return true;
        }
        else
        {
            return false;
        }
        //End of while
    }
}

bool PhysicalConnection::OnSendCompleted(int /*dwIoSizeUnused*/, bool& bIsBufferIdle)
{
    ScopedLock lock(csLock);

	if(status < WaitingForWrite)
	{
		return false;
	}

    bWriteInProgress = FALSE;

	if(!WriteBytes())
		return false;

    bIsBufferIdle = (oBuffer.getDataSize() == 0 && !bWriteInProgress);
    if(bIsBufferIdle && status == WaitingForWrite)
	{
		CloseSocket(); 
        return false;
	}

    return true;
}

void PhysicalConnection::closeConnection(bool bWaitForSendsToComplete)
{
    ScopedLock lock(csLock);

    if (status < Connected)
    {
        return;
    }

    //Either connected or attached :
    if (bWaitForSendsToComplete)
    {
        if (oBuffer.getDataSize() == 0)
        {
            CloseSocket();
        }
        else
            status = WaitingForWrite;
    }
    else
    {
        CloseSocket();
    }
}

void PhysicalConnection::CloseSocket()
{
    ::close(socket);
    status = Disposable;
}

bool PhysicalConnection::checkIfUnusedByIOWorkers()
{
	/* In Linux there is an API defect with epoll_wait.
	In PF I'm using a trick to detect the safe moment of release of the
	custom data attached to the socket.
	I will wait until EPOLL_CTL_DISABLE comes top Linux kernel
	before changing the logic. (In Windows we are testing on the 
	ioWorkersReferenceCounter).
	*/
	return status == Disposable /*&& ioWorkersReferenceCounter == 0*/;
}

}
