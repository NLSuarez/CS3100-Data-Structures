// *********************************************************
// Implementation file Heap.cpp for the ADT heap.
// *********************************************************
#include "Heap.h"  // header file for heap

heapClass::heapClass() : Size(0)
{
}  // end default constructor

bool heapClass::HeapIsEmpty() const
{
   return bool(Size == 0);
}  // end HeapIsEmpty

void heapClass::HeapInsert(const heapItemType& NewItem, 
                           bool& Success)
// Method: Inserts the new item after the last item in the
// heap and trickles it up to its proper position. The
// heap is full when it contains MAX_HEAP items.
{
   Success = bool(Size < MAX_HEAP);

   if (Success)
   {  // place the new item at the end of the heap
      Items[Size] = NewItem;

      // trickle new item up to its proper position
      int Place = Size;
      int Parent = (Place - 1)/2;
      while ( (Parent >= 0) &&
              (Items[Place].Key() > Items[Parent].Key()) )
      {  // swap Items[Place] and Items[Parent]
         heapItemType Temp = Items[Parent];
         Items[Parent] = Items[Place];
         Items[Place] = Temp;

         Place = Parent;
         Parent = (Place -1 )/2;
      }  // end while

      ++Size;
   }  // end if
}  // end HeapInsert

void heapClass::HeapDelete(heapItemType& RootItem, 
                           bool& Success)
// Method: Swaps the last item in the heap with the root
// and trickles it down to its proper position.
{
   Success = bool(!HeapIsEmpty());

   if (Success)
   {  RootItem = Items[0];
      Items[0] = Items[--Size];
      RebuildHeap(0);
   }  // end if
}  // end HeapDelete

void heapClass::RebuildHeap(int Root)
{
   // if the root is not a leaf and the root's search key 
   // is less than the larger of the search keys in the 
   // root's children
   int Child = 2 * Root + 1;  // index of root's left 
                              // child, if any
   if ( Child < Size )
   {  // root is not a leaf, so it has a left child at Child
      int RightChild = Child + 1;  // index of right child, 
                                   // if any

      // if root has a right child, find larger child
      if ( (RightChild < Size) &&
           (Items[RightChild].Key() > Items[Child].Key()) )
         Child = RightChild;  // index of larger child

      // if the root's value is smaller than the
      // value in the larger child, swap values
      if ( Items[Root].Key() < Items[Child].Key() )
      {  heapItemType Temp = Items[Root];
         Items[Root] = Items[Child];
         Items[Child] = Temp;

         // transform the new subtree into a heap
         RebuildHeap(Child);
      }  // end if
   }  // end if

   // if root is a leaf, do nothing
}  // end RebuildHeap
// End of implementation file.
