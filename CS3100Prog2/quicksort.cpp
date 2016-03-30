
/* I furnished parameters c_count and m_count are here, for
   counting list element comparisons and list element moves. */

#include "swap.h"

void choosePivot(int theArray[ ], int first, int last)
// ---------------------------------------------------------
// Chooses a pivot for quicksorts partition algorithm and
// swaps it with the first item in an array.
// Precondition: theArray[first..last] is an array;
// first <= last.
// Postcondition: theArray[first] is the pivot.
// ---------------------------------------------------------
{

    /* Do nothing, so the pivot is just the first element of the array.
       Don't change this code because we want all members of the class to
       work with the same version of the quicksort. */
        
}

void partition(int theArray[ ], int first, int last, int &pivotIndex, 
                 unsigned long int & c_count, unsigned long int & m_count)
// ---------------------------------------------------------
// Partitions an array for quicksort.
// Precondition: theArray[first..last] is an array;
// first <= last.
// Postcondition: Partitions theArray[first..last] such
// that:
// S1 = theArray[first..pivotIndex-1] < pivot
// theArray[pivotIndex] == pivot
// S2 = theArray[pivotIndex+1..last] >= pivot
// Calls: choosePivot and swap.
// ---------------------------------------------------------
{
   // place pivot in theArray[first]
   choosePivot(theArray, first, last);

   int pivot = theArray[first]; // copy pivot
   ++m_count;
       
   // initially, everything but pivot is in unknown
   int lastS1 = first;		 // index of last item in S1
   int firstUnknown = first + 1; // index of first item in
				 // unknown

   // move one item at a time until unknown region is empty
   for (; firstUnknown <= last; ++firstUnknown)
   {  // Invariant: theArray[first+1..lastS1] < pivot
      // theArray[lastS1+1..firstUnknown-1] >= pivot
      // move item from unknown to proper region

      if  (++c_count && (theArray[firstUnknown] < pivot)) 
      {	 // item from unknown belongs in S1
	 ++lastS1;
	 swap(theArray[firstUnknown], theArray[lastS1]);
	 m_count += 3;
      }	 // end if
      // else item from unknown belongs in S2
   }  // end for

   // place pivot in proper position and mark its location
   swap(theArray[first], theArray[lastS1]);
   m_count += 3;
   pivotIndex = lastS1;
} // end partition


void quicksort(int theArray[ ], int first, int last, 
                unsigned long int & c_count, unsigned long int & m_count)
// ---------------------------------------------------------
// Sorts the items in an array into ascending order.
// Precondition: theArray[first..last] is an array.
// Postcondition: theArray[first..last] is sorted.
// Calls: partition.
// ---------------------------------------------------------
{
   int pivotIndex;
   if (first < last)
   {  // create the partition: S1, pivot, S2
      partition(theArray, first, last, pivotIndex, c_count, m_count);
      // sort regions S1 and S2
      quicksort(theArray, first, pivotIndex-1, c_count, m_count);
      quicksort(theArray, pivotIndex+1, last, c_count, m_count);
   } // end if
} // end quicksort
