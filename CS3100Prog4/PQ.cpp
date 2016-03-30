// *********************************************************
// Implementation file PQ.cpp for the ADT priority queue.
// A heap represents the priority queue.
// *********************************************************
#include "PQ.h"    // header file for priority queue

bool pqClass::PQueueIsEmpty() const
{
   return H.HeapIsEmpty();
}  // end PQueueIsEmpty

void pqClass::PQueueInsert(const pqItemType& NewItem, 
                           bool& Success)
{
   H.HeapInsert(NewItem, Success);
}  // end PQueueInsert

void pqClass::PQueueDelete(pqItemType& PriorityItem, 
                           bool& Success)
{
   H.HeapDelete(PriorityItem, Success);
}  // end PQueueDelete
// End of implementation file.
