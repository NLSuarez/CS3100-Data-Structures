// *********************************************************
// Header file ListP.h for the ADT list.
// Pointer-based implementation.
// *********************************************************
#ifndef LIST_CLASS
#define LIST_CLASS
#include <string>
#include <iostream>

using namespace std ;

typedef string listItemType;

struct listNode;            // linked list node
typedef listNode* lPtrType;  // pointer to node

class listClass
{
public:
// constructors and destructor:
   listClass();                    // default constructor
   listClass(const listClass& L);  // copy constructor
   ~listClass();                   // destructor

// list operations:
   bool ListIsEmpty() const;
   int ListLength() const;
   void ListInsert(int NewPosition, listItemType NewItem,
                   bool& Success);
   void ListDelete(int Position, bool& Success);
   void ListRetrieve(int Position, listItemType& DataItem, 
                     bool& Success) const;
   //Different from ListRetrieve. Will retrieve a specific item
   //in the list
   void ListItemRetrieve(listItemType DataItem, bool& Success,
        int& Position) const;
   void ListPrint() ;

private:
   int     Size;  // number of items in list
   lPtrType Head;  // pointer to linked list of items

   lPtrType PtrTo(int Position) const;
   // Returns a pointer to the Position-th node 
   // in the linked list.

}; // end class
// End of header file.

#endif
