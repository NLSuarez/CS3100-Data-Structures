// *********************************************************
// Header file Heap.h for the ADT heap.
// *********************************************************

#include "Data.h"  // definition of itemClass

//const int MAX_HEAP = maximum-size-of-heap;
const int MAX_HEAP = 20; // this is the value specified in the assignment
//typedef desired-type-of-search-key keyType;
typedef itemClass keyType; // this is one way to do it
              /* You have to decide what the keyType should be,
                 as part of your design.  So you need to change
                 the line above if you want something else 
                 besides the itemClass to be the keyType. */

typedef itemClass heapItemType;

class heapClass
{
public:
   heapClass();  // default constructor
   // copy constructor and destructor are
   // supplied by the compiler

// heap operations:
   virtual bool HeapIsEmpty() const;
   // Determines whether a heap is empty.
   // Precondition: None.
   // Postcondition: Returns true if the heap is empty;
   // otherwise returns false.

   virtual void HeapInsert(const heapItemType& NewItem, 
                           bool& Success);
   // Inserts an item into a heap.
   // Precondition: NewItem is the item to be inserted.
   // Postcondition: If the heap was not full, NewItem is
   // in its proper position and Success is true; 
   // otherwise Success is false.

   virtual void HeapDelete(heapItemType& RootItem, 
                           bool& Success);
   // Retrieves and deletes the item in the root of a heap.
   // This item has the largest search key in the heap.
   // Precondition: None.
   // Postcondition: If the heap was not empty, RootItem 
   // is the retrieved item, the item is deleted from the
   // heap, and Success is true. However, if the heap was
   // empty, removal is impossible and Success is false.

protected:
   void RebuildHeap(int Root);
   // Converts the semiheap rooted at index Root 
   // into a heap.

private:
   heapItemType Items[MAX_HEAP];  // array of heap items
   int          Size;             // number of heap items
};  // end class
// End of header file.
