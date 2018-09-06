#include "stdafx.h"
#include "WebsocketContext.h"


WebsocketContext::WebsocketContext(void)
	:bufferedContent(RecyclableBuffer::Single)
{
	currentContinuationOpCode = -1;
}


WebsocketContext::~WebsocketContext(void)
{
}

void WebsocketContext::recycle()
{
	bufferedContent.clearBytes();
	currentContinuationOpCode = -1;
}
