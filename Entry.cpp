//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

#include "Entry.h"

#ifndef ENTRY_CPP
#define ENTRY_CPP

template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rightHandItem) const
{
   return (searchKey == rightHandItem.getKey());
}  // end operator==

template <class KeyType, class ItemType>
Entry<KeyType, ItemType>::Entry() : item(0), searchKey("")
{
}

template <class KeyType, class ItemType>
Entry<KeyType, ItemType>::Entry(ItemType newEntry, KeyType sKey):
item(newEntry), searchKey(sKey)
{

}

template <class KeyType, class ItemType>
ItemType  Entry<KeyType, ItemType>::getItem() const
{
	return item;
}

template <class KeyType, class ItemType>
KeyType  Entry<KeyType, ItemType>::getKey() const
{
	return searchKey;
}

template <class KeyType, class ItemType>
void  Entry<KeyType, ItemType>::setItem(const ItemType& newEntry)
{
	item = newEntry;
}

template <class KeyType, class ItemType>
bool  Entry<KeyType, ItemType>::operator>(const Entry<KeyType, ItemType>& rightHandItem) const
{
	return (searchKey > rightHandItem.getKey());
}

template <class KeyType, class ItemType>
void Entry<KeyType, ItemType>::setKey(const KeyType& sKey)
{
	searchKey = sKey;
}
#endif