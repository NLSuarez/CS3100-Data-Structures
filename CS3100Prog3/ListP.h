#ifndef my_LISTP_H 
#define my_LISTP_H 

// =========================================================
// Header file ListP.h for the ADT list.
// Pointer-based implementation.
// =========================================================

#include "ListException.h"
#include "ListIndexOutOfRangeException.h"
#include <string>

// Must define ListItemType before compilation
typedef string ListItemType;

class List
{
   public:
   // constructors and destructor:
      List();                  // default constructor
      List(const List& aList); // copy constructor
      ~List();                 // destructor
   
   // list operations:
      bool isEmpty() const;
      int getLength() const;
      void insert(int index, ListItemType newItem)
            throw(ListIndexOutOfRangeException, ListException);
      void remove(int index)
            throw(ListIndexOutOfRangeException);
      void retrieve(int index, ListItemType& dataItem) const
            throw(ListIndexOutOfRangeException);
   
         /* The purpose of copyListNodes is to make the caller equal
            to a duplicate copy of aList.  Before making the call,
            the caller must be empty. */
   
      void copyListNodes (const List & aList)
            throw(ListException);
   
         /* The purpose of removeAll is to make the caller empty. */
   
      void removeAll () ;
   
         /* This is the overloaded assignment operator for the 
            List class. */
   
      List & operator=(const List& rhs);
   
   private:
      struct ListNode // a node on the list
      {
         ListItemType item; // a data item on the list
         ListNode *next;    // pointer to next node
      }; // end struct
   
      int size;       // number of items in list
      ListNode *head; // pointer to linked list of items
   
      ListNode *find(int index) const;
      // Returns a pointer to the index-th node
      // in the linked list.
   }; // end class
// End of header file.

#endif

