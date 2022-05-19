#include "HashedEntry.h"

#ifndef HASHED_ENTRY_CPP
#define HASHED_ENTRY_CPP
template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry()
{
	nextPtr = nullptr;
}

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(ItemType newEntry, KeyType sKey) :
nextPtr(nullptr)
{
    //Entry<KeyType, ItemType>(newEntry, sKey);
	Entry<KeyType, ItemType>::setKey(sKey);
	Entry<KeyType, ItemType>::setItem(newEntry);
}

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(ItemType newEntry, KeyType sKey,
	HashedEntry<KeyType, ItemType>* nextEntryPtr):
	nextPtr(nextEntryPtr)
{
    //Entry<KeyType, ItemType>(newEntry, sKey);
	Entry<KeyType, ItemType>::setKey(sKey);
	Entry<KeyType, ItemType>::setItem(newEntry);
}

template <class KeyType, class ItemType>
void HashedEntry<KeyType, ItemType>::setNext(HashedEntry<KeyType, ItemType>* nextEntryPtr)
{
	nextPtr = nextEntryPtr;
}

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedEntry<KeyType, ItemType>::getNext() const
{
	return nextPtr;
}
#endif