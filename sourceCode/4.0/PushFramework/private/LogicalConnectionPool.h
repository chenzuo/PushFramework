/********************************************************************
	File :			LogicalConnectionPool.h
	Creation date :	3/5/2014

	License :			Copyright 2010-2014 Ahmed Charfeddine, http://www.pushframework.com

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
#pragma once

namespace PushFramework
{
	class ServerImpl;
	class LogicalConnectionPool : public AbstractPool
	{
	public:
		LogicalConnectionPool(ServerImpl* pServerImpl);
		~LogicalConnectionPool(void);

	protected:
		virtual void deleteImpl(ObjectPtr obj);
		virtual ObjectPtr createImpl();
		virtual void recycleObject(ObjectPtr p);

	private:
		ServerImpl* pServerImpl;
	};
}
