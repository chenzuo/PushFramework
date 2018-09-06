/********************************************************************
	File :			XMLProtocol.h
	Creation date :	2012/01/29

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
#ifndef XMLProtocol__INCLUDED
#define XMLProtocol__INCLUDED


namespace PushFramework
{
class XMLProtocol : public Protocol
{
public:
    XMLProtocol(void);
    ~XMLProtocol(void);

	virtual ProtocolContext* createNewProtocolContext();
	virtual void startSession(ProtocolContext& context, Buffer& outgoingBytes);
	virtual bool readData(ProtocolContext& context, Buffer& incomingBytes);
	virtual DecodeResult::Type tryDecode(ProtocolContext& context, Buffer& outputBuffer);
	virtual EncodeResult::Type encodeContent(ProtocolContext& context, Buffer& inputBuffer, Buffer& outputBuffer);
};
}



#endif // XMLProtocol__INCLUDED
