#ifndef my_KEYEDITEM_H 
#define my_KEYEDITEM_H 

// *********************************************************
// Header file KeyedItem.h for the ADT binary search tree.
// *********************************************************
#include <string>
#include "ListP.h"

typedef string KeyType;

class KeyedItem
{
   public:
      KeyedItem() {};
      
      KeyedItem(const KeyType& name, const List & attrs, bool flag) 
             : searchKey(name),
                 isSuspect(flag) 
      {
         attributes = attrs ;
      };
      
      KeyedItem(const KeyType& name) : searchKey(name) {};
      
      KeyType getKey() const
      {
         return searchKey;
      } // end getKey
   
      KeyedItem & operator=(const KeyedItem& rhs)
      {
         /* Check for assignment to self. */
   
        if (this != &rhs)
        {
            /* We make sure to get a deep copy of attributes.
               The assignment operator used on the attributes is overloaded.
               It is defined in ListP.h and ListP.cpp. */
          attributes = rhs.attributes ; 
          searchKey = rhs.searchKey ;
          isSuspect = rhs.isSuspect ;
        }
        return *this ;
      }
   
      List attributes ;
      KeyType searchKey;
      bool isSuspect ;
   
}; // end class
   
#endif
