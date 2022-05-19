//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 18-4.

/** A binary search tree implementation of the ADT dictionary
    that organizes its data items in sorted search-key order.
    Search keys in the dictionary are unique.
 @file HashDictionary.h */
 
#ifndef _HASHED_DICTIONARY
#define _HASHED_DICTIONARY

#include "DictionaryInterface.h"
#include "HashedEntry.h"
#include <string>
#include <fstream>
//#include "NotFoundException.h"
using std::string;

const int TABLE_SIZE = 11;

template <class KeyType, class ItemType>
class HashedDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
   // Binary search tree of dictionary entries
   HashedEntry<KeyType, ItemType> *hashTable[TABLE_SIZE];
   int ItemCount;
   
   //void traversalHelper(Entry<KeyType, ItemType>& theEntry);
    int getHashIndex(const KeyType&)const;
   
   
public:
   HashedDictionary();
   //HashedDictionary(const HashedDictionary<KeyType, ItemType>& dict);
   virtual ~HashedDictionary();
   
   // The declarations of the public methods appear here and are the
   // same as given in Listing 18-3 for the class ArrayDictionary.
   
   bool isEmpty() const;
   int getNumberOfItems() const;
    bool add(const KeyType& searchKey, const ItemType& newItem);
   bool remove(const KeyType& searchKey);
   void clear();
   ItemType getItem(const KeyType& searchKey) const; // throw (NotFoundException);
   bool contains(const KeyType& searchKey) const;
   
   /** Traverses the items in this dictionary in sorted search-key order
    and calls a given client function once for each item. */
   void traverse(void visit(ItemType&)) const;
   /***function saves data to file */
    bool save2File(string fileName);
    
}; // end HashedDictionary

#include "HashedDictionary.cpp"
#endif
