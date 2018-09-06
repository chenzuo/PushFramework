/********************************************************************
	File :			DataBuffer.cpp
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
#include "../include/DataBuffer.h"


namespace PushFramework
{


DataBuffer::DataBuffer(unsigned int uMaxSize)
{
    uSize = 0;
    allocate(uMaxSize);
}

DataBuffer::DataBuffer()
{
    uSize = 0;
    pBuffer = NULL;
}

void DataBuffer::allocate( unsigned int uMaxSize )
{
    this->uMaxSize = uMaxSize;
    pBuffer = new char[uMaxSize];
}

DataBuffer::~DataBuffer(void)
{
    delete[] pBuffer;
}
bool DataBuffer::append( char* _pBuffer, unsigned int _uSize )
{  
    if(getRemainingSize() < _uSize)
        return false;

    //Copy the data :
    ::memcpy(pBuffer+uSize, _pBuffer, _uSize);

    //Update the size of the buffer.
    uSize+=_uSize;

    return true;
}

bool DataBuffer::append( unsigned char* _pBuffer, unsigned int _uSize )
{
    return append((char*) _pBuffer, _uSize);
}

void DataBuffer::pop( unsigned int _uSize )
{
    uSize -= _uSize;
    if(uSize == 0){
        return;
    }
    ::memmove(pBuffer, pBuffer+_uSize, uSize);
}

unsigned int DataBuffer::getDataSize()
{
    return uSize;
}

unsigned int DataBuffer::getMaxDataSize()
{
    return uMaxSize;
}

char* DataBuffer::getBuffer()
{
    return pBuffer;
}

unsigned int DataBuffer::getRemainingSize()
{
    return uMaxSize - uSize;
}

void DataBuffer::growSize( unsigned int growBy )
{
    uSize += growBy;
}

char DataBuffer::getAt( int offset )
{
    return pBuffer[offset];
}


}

