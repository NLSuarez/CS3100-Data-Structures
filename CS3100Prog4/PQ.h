// *********************************************************
// Header file PQ.h for the ADT priority queue.
// Heap implementation.
// *********************************************************
#include "Heap.h"  // ADT heap operations
typedef heapItemType pqItemType;

class pqClass
{
public:
   // default constructor, copy constructor, and
   // destructor are supplied by the compiler

// priority-queue operations:
   virtual bool PQueueIsEmpty() const;
   virtual void PQueueInsert(const pqItemType& NewItem, 
                             bool& Success);
   virtual void PQueueDelete(pqItemType& PriorityItem, 
                             bool& Success);
   
private:
   heapClass H;
};  // end class
// End of header file.
