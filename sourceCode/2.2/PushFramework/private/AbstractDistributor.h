/********************************************************************
	File :			AbstractDistributor.h
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
#ifndef AbstractDistributor__INCLUDED
#define AbstractDistributor__INCLUDED

#pragma once

namespace PushFramework
{


typedef void* ItemPtr;
enum ProcessResult {DeleteItem, PauseProcessing, ContinueProcessing};

/*The AbstractDistributor launches a thread that streams packets in Broadcast Queues
 *to a collection of Logical Connections.
 *Streaming is time critical, so locking is reduced to a minimum, and we try to simplify the list
 *that the thread is processing by temporary retiring clients that got all the data into an inactiveList
 *until a change is brought to a Broadcast Queue (reshuffle is triggered by BroadcastQueue::PushPacket)
*/

class AbstractDistributor
{
public:
    AbstractDistributor(void);

    virtual ~AbstractDistributor(void);

    void reshuffle();

    virtual void addItem(ItemPtr pItem);
    void removeItem(ItemPtr pItem);
	void reactivateItem(ItemPtr pItem);

    int getItemsCount();

    void start();
    void stop();

protected:
    virtual ProcessResult processItem(ItemPtr pItem) = 0;
    virtual void handleItemRemoved(ItemPtr pItem) = 0;
private:
    int itemsCount;
    typedef list<ItemPtr> itemListT;

    itemListT activeList;
    itemListT inactiveList;
    itemListT insertedItemsList;
    itemListT removedItemsList;
	itemListT reactivatedItemsList;

    bool reactivateAllItems;
    bool processAddedItems;
    bool processRemovedItems;
	bool processReactivatedItems;

    bool shouldStop;
    ThreadHandleType hThread;

    CRITICAL_SECTION cs_SharedLists;

    bool checkMergeNewInsertedItems();
    bool checkMergeInactiveItems();
    bool checkMergeReactivatedItems();
	void checkRemoveItems();


    void processActiveList();

    void doWork();

    static bool removeFromList(itemListT& itemList, ItemPtr pItem);
    void clearList(itemListT& itemList);


#ifdef Plateform_Windows
    static DWORD WINAPI threadProc(LPVOID lpVoid);
#else
#ifdef Plateform_Linux
    static void* threadProc(void* lpVoid);
#endif
#endif

};
}


#endif // AbstractDistributor__INCLUDED
