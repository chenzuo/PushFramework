/********************************************************************
	File :			ObjectPool.h
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


************
*********************************************************/
#ifndef ObjectPool__INCLUDED
#define ObjectPool__INCLUDED

#pragma once
#include "ScopedLock.h"
#include <map>


namespace PushFramework
{

template<class T>
class ObjectPool
{
public:
    typedef vector<T*> objVectT;
	ObjectPool()
	{
		::InitializeCriticalSection(&cs);
	}
	~ObjectPool(void)
	{
		typename objVectT::iterator it;
		for (it = objVect.begin(); it != objVect.end() ;it++)
			delete (*it);
		objVect.clear();

		DeleteCriticalSection(&cs);
	}

	void initialize(unsigned int nMaxObjects)
	{
		for (unsigned int i=0;i<nMaxObjects;i++)
			objVect.push_back(new T());
	}
	T* createObject()
	{
		ScopedLock lock(cs);
		if (objVect.empty())
			return NULL;

		T* p = objVect.back();
		objVect.pop_back();
		return p;
	}
	void deleteObject(T* p)
	{
		ScopedLock lock(cs);
		objVect.push_back(p);
	}
private:
	CRITICAL_SECTION cs;
	objVectT objVect;
	
};

}

#endif // ObjectPool__INCLUDED
