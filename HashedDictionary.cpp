//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

// PARTIALLY COMPLETE
#include "HashedDictionary.h"
#include <string>
#include <iostream>
#ifndef HASHED_DICTIONARY_CPP
#define HASHED_DICTIONARY_CPP

using namespace std;

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	for (int index = 0; index < TABLE_SIZE; index++)
		hashTable[index] = nullptr;
    ItemCount = 0;
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary()
{
	clear();
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &sKey) const
{
    int i = 0;
    for(int x = 0; x< sKey.length(); x++){
         i +=sKey[x];
    }
    return i % TABLE_SIZE;
    
}


template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
   // Create entry to add to dictionary
   HashedEntry<KeyType, ItemType>* entryToAddPtr =
                  new HashedEntry<KeyType, ItemType>(newItem, searchKey);
   
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   
   // Add the entry to the chain at itemHashIndex
   if (hashTable[itemHashIndex] == nullptr)
   {
      hashTable[itemHashIndex] = entryToAddPtr;
       ItemCount++;
   }
   else
   {
      entryToAddPtr->setNext(hashTable[itemHashIndex]);
      hashTable[itemHashIndex] = entryToAddPtr;
      ItemCount++;
   } // end if

    
   return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
   bool itemFound = false;
   
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   if (hashTable[itemHashIndex] != nullptr)
   {
      // Special case - first node has target
      if (searchKey == hashTable[itemHashIndex]->getKey())
      {
         HashedEntry<KeyType, ItemType>* entryToRemovePtr =
         hashTable[itemHashIndex];
         hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
         delete entryToRemovePtr;
         entryToRemovePtr = nullptr; // For safety
         itemFound = true;
  
      }
      else // Search the rest of the chain
      {
         HashedEntry<KeyType, ItemType>* prevPtr = hashTable[itemHashIndex];
         HashedEntry<KeyType, ItemType>* curPtr = prevPtr->getNext();
         while ((curPtr != nullptr) && !itemFound )
         {
            // Found item in chain so remove that node
            if (searchKey == curPtr->getKey())
            {
               prevPtr->setNext(curPtr->getNext());
               delete curPtr;
               curPtr = nullptr; // For safety
               itemFound = true;
             
             
            }
            else // Look at next entry in chain
            {
               prevPtr = curPtr;
               curPtr = curPtr->getNext();
            } // end if
         } // end while
             
      } // end if
      
   } // end if
       
   if(itemFound == true){
        ItemCount--;
   }
   
   return itemFound;
} // end remove

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const
{
    return getNumberOfItems()==0;
    
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const
{
    return ItemCount;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	for (int x = 0; x < TABLE_SIZE; x++)
	{
		HashedEntry<KeyType, ItemType>* ptr = hashTable[x];
		while (ptr != nullptr)
		{
			hashTable[x] = ptr->getNext();
			ptr->setNext(nullptr);
			delete ptr;
			ptr = hashTable[x];
		}
	}
    ItemCount = 0;
}

template <class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType& searchKey) const
{
    bool itemFound = false;
    ItemType entryToReturn = 0;
    // Compute the hashed index into the array
    int itemHashIndex = getHashIndex(searchKey);
    if (hashTable[itemHashIndex] != nullptr)
    {
       // Special case - first node has target
       if (searchKey == hashTable[itemHashIndex]->getKey())
       {
          entryToReturn = hashTable[itemHashIndex]->getItem();
          itemFound = true;
       }
       else // Search the rest of the chain
       {
          HashedEntry<KeyType, ItemType>* chainptr = hashTable[itemHashIndex];
       
          while ((chainptr!= nullptr) && !itemFound )
          {
             // Found item in chain so remove that node
             if (searchKey == chainptr->getKey())
             {
                 entryToReturn = chainptr->getItem();
                 itemFound = true;
             }
             else // Look at next entry in chain
                 chainptr = chainptr->getNext();
             } // end if
          } // end while
       } // end if


    return entryToReturn;
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType& searchKey) const
{
    bool itemFound = false;
    // Compute the hashed index into the array
    int itemHashIndex = getHashIndex(searchKey);
    if (hashTable[itemHashIndex] != nullptr)
    {
       // Special case - first node has target
       if (searchKey == hashTable[itemHashIndex]->getKey())
       {
          itemFound = true;
       }
       else // Search the rest of the chain
       {
          HashedEntry<KeyType, ItemType>* chainptr = hashTable[itemHashIndex];
       
          while ((chainptr!= nullptr) && !itemFound )
          {
             // Found item in chain so remove that node
             if (searchKey == chainptr->getKey())
             {
                 itemFound = true;
             }
             else // Look at next entry in chain
                 chainptr = chainptr->getNext();
             } // end if
          } // end while
       } // end if


    return itemFound;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(ItemType&)) const
{
    for (int index = 0; index < TABLE_SIZE; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            cout << "Sloth #" << index << ", " << chainPtr->getKey();
            visit(currentItem);
            chainPtr = chainPtr->getNext();
            }
        }
}

//HashedDictionary<std::string, int> xyz;
template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::save2File(string fileName){
    ofstream outFile;
    bool is_saved = false;
    outFile.open(fileName);
    if(outFile.is_open()){
        for (int index = 0; index < TABLE_SIZE; index++) {
            HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
            while (chainPtr != nullptr) {
                outFile << chainPtr->getItem() << " " << chainPtr->getKey() << "\n";
                chainPtr = chainPtr->getNext();
                }
        }
        outFile.close();
        is_saved = true;
    }
    else{
        is_saved = false;
    }
    return is_saved;

}

#endif
