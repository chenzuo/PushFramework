/********************************************************************
	File :			DataBuffer.h
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
#ifndef DataBuffer__INCLUDED
#define DataBuffer__INCLUDED

#pragma once

#include "PushFramework.h"

namespace PushFramework
{


class PUSHFRAMEWORK_API DataBuffer
{
public:
    DataBuffer(unsigned int uMaxSize);
    DataBuffer();
    ~DataBuffer(void);

    void allocate(unsigned int uMaxSize);
    bool append(char* _pBuffer, unsigned int _uSize);
    bool append(unsigned char* _pBuffer, unsigned int _uSize);
    void pop(unsigned int _uSize);
    unsigned int getDataSize();
    unsigned int getMaxDataSize();
    char* getBuffer();
    void growSize(unsigned int growBy);
    unsigned int getRemainingSize();
    char getAt(int offset);
private:
    char* pBuffer;
    unsigned int uSize;
    unsigned int uMaxSize;
};

}

#endif // DataBuffer__INCLUDED
