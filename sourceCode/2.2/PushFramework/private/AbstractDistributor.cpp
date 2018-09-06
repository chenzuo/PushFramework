/********************************************************************
	File :			AbstractDistributor.cpp
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
#include "StdAfx.h"
#include "AbstractDistributor.h"
#include "ScopedLock.h"


namespace PushFramework
{
AbstractDistributor::AbstractDistributor( void )
{
    shouldStop = false;
    itemsCount = 0;
    InitializeCriticalSection(&cs_SharedLists);

    reactivateAllItems = false;
    processRemovedItems = false;
    processAddedItems = false;
	processReactivatedItems = false;
}



AbstractDistributor::~AbstractDistributor( void )
{
    DeleteCriticalSection(&cs_SharedLists);
}

void AbstractDistributor::reshuffle()
{
    reactivateAllItems = true;
}


bool AbstractDistributor::checkMergeInactiveItems()
{
    bool ret = false;

	if (reactivateAllItems)
	{
		reactivateAllItems = false;

		if(!inactiveList.empty())
			ret = true;

		activeList.splice(activeList.end(), inactiveList);
	}

	/*TODO restore this and add events to replace Sleep in doWork.
    if (CompareAndSwap(&reactivateAllItems, false, true))
    {
        if(!inactiveList.empty())
            ret = true;

        activeList.splice(activeList.end(), inactiveList);
    }*/

    return ret;
}

void AbstractDistributor::addItem( ItemPtr pItem )
{
    ScopedLock lock(cs_SharedLists);

    insertedItemsList.push_back(pItem);
    processAddedItems = true;
    itemsCount++;
}

void AbstractDistributor::removeItem( ItemPtr pItem )
{
    ScopedLock lock(cs_SharedLists);

    if(removeFromList(insertedItemsList, pItem))
    {
        itemsCount--;
        handleItemRemoved(pItem);
        return;
    }

    removedItemsList.push_back(pItem);
    processRemovedItems = true;
}


void AbstractDistributor::doWork()
{
    while (!shouldStop)
    {
        checkRemoveItems();
        if (checkMergeNewInsertedItems() || checkMergeInactiveItems() || checkMergeReactivatedItems() )
        {
            processActiveList();
        }
        else
        {
            Sleep(10);
        }
    }
}

bool AbstractDistributor::checkMergeNewInsertedItems()
{
    bool ret = false;
    if (processAddedItems)
    {
        ScopedLock lock(cs_SharedLists);
        if (!insertedItemsList.empty())
            ret = true;
        
        activeList.splice(activeList.end(), insertedItemsList);

        processAddedItems = false;
    }
    return ret;
}


void AbstractDistributor::checkRemoveItems()
{
    if (processRemovedItems)
    {
        ScopedLock lock(cs_SharedLists);
        itemListT::iterator it = removedItemsList.begin();
        while (it != removedItemsList.end())
        {
            ItemPtr pItem = *it;
            if (removeFromList(inactiveList, pItem) || removeFromList(activeList, pItem))
            {
                handleItemRemoved(pItem);
                itemsCount--;
            }
            it++;
        }
        //
        removedItemsList.clear();
        processRemovedItems = false;
    }
}



void AbstractDistributor::processActiveList()
{
    itemListT::iterator it = activeList.begin();

    while(it != activeList.end())
    {
        ItemPtr pItem = *it;

        ProcessResult result = processItem(pItem);

        if(result == DeleteItem)
        {
            handleItemRemoved(pItem);
            it = activeList.erase(it);
            itemsCount--;
        }
        if (result == PauseProcessing)
        {
            inactiveList.push_back(pItem);
            it = activeList.erase(it);
        }
        if (result == ContinueProcessing)
        {
            it++;
        }
        //
        if (it == activeList.end())
        {
            if (shouldStop)
            {
                return;
            }
            checkRemoveItems();
            checkMergeNewInsertedItems();
            checkMergeInactiveItems();
			checkMergeReactivatedItems();
            it = activeList.begin();
        }
    }
}

int AbstractDistributor::getItemsCount()
{
    return itemsCount;
}

void AbstractDistributor::start()
{
#ifdef Plateform_Windows
    DWORD  nThreadID;

    hThread = CreateThread(NULL,// Security
                                     0,						// Stack size - use default
                                     threadProc,     		// Thread fn entry point
                                     (void*) this,			// Param for thread
                                     0,						// Init flag
                                     &nThreadID);			// Thread address
#else
#ifdef Plateform_Linux
    pthread_create(&hThread, NULL, threadProc, (void*) this);
#endif
#endif
}

void AbstractDistributor::stop()
{
    shouldStop = true;
#ifdef Plateform_Windows
    WaitForSingleObject(hThread, INFINITE);
#else
#ifdef Plateform_Linux
    pthread_join(hThread, NULL);
#endif
#endif
	clearList(insertedItemsList);
	clearList(removedItemsList);
	clearList(inactiveList);
	clearList(activeList);
}

#ifdef Plateform_Windows
DWORD WINAPI AbstractDistributor::threadProc(LPVOID lpVoid)
#else
#ifdef Plateform_Linux
void* AbstractDistributor::threadProc(void* lpVoid)
#endif
#endif
{
    AbstractDistributor* pMe = reinterpret_cast<AbstractDistributor*> (lpVoid);
    pMe->doWork();
#ifdef Plateform_Windows
    return 0;
#endif
}

bool AbstractDistributor::removeFromList( itemListT& itemList, ItemPtr pItem )
{
    itemListT::iterator it = itemList.begin();
    while (it!=itemList.end())
    {
        if (pItem == (*it))
        {
            itemList.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

void AbstractDistributor::clearList( itemListT& itemList )
{
	while (!itemList.empty())
	{
		ItemPtr pItem = itemList.front();
		itemList.pop_front();
		handleItemRemoved(pItem);
	}
}

void AbstractDistributor::reactivateItem( ItemPtr pItem )
{
	ScopedLock lock(cs_SharedLists);

	reactivatedItemsList.push_back(pItem);
	processReactivatedItems = true;
}

bool AbstractDistributor::checkMergeReactivatedItems()
{
	bool ret = false;

	if (processReactivatedItems)
	{
		ScopedLock lock(cs_SharedLists);

		for (itemListT::iterator it = reactivatedItemsList.begin();
			it!=reactivatedItemsList.end();
			it++)
		{
			ItemPtr pItem = *it;
			//
			for (itemListT::iterator it2 = inactiveList.begin();
				it2 != inactiveList.end();
				it2 ++)
			{
				if (pItem == *it2)
				{
					inactiveList.erase(it2);
					activeList.push_back(pItem);
					ret = true;
					break;
				}
			}
		}

		reactivatedItemsList.clear();
		processReactivatedItems = false;
	}

	return ret;
}


}
