
/* I furnished parameters c_count and m_count are here, for
   counting list element comparisons and list element moves. */

#include "swap.h"

int indexOfLargest ( const int theArray[], int size, 
                       unsigned long int & c_count )
// ---------------------------------------------------
// Finds the largest item in an array.
// Precondition: theArray is an array of size items,
// size >= 1.
// Postcondition: Returns the index of the largest
// item in the array. The arguments are unchanged.
// ---------------------------------------------------
{
   int indexSoFar = 0; // index of largest item
		       // found so far

   for (int currentIndex = 1; currentIndex < size; ++currentIndex)
   {  // Invariant: theArray[indexSoFar] >=
      // theArray[0..currentIndex-1]

      if ( ++c_count && ((theArray[currentIndex] > theArray[indexSoFar])) )
	     indexSoFar = currentIndex;
   } // end for

   return indexSoFar; // index of largest item
} // end indexOfLargest


void selectionSort(int theArray[], int n, 
         unsigned long int & c_count, unsigned long int & m_count) 
// ---------------------------------------------------
// Sorts the items in an array into ascending order.
// Precondition: theArray is an array of n items.
// Postcondition: The array theArray is sorted into
// ascending order; n is unchanged.
// Calls: indexOfLargest, swap.
// ---------------------------------------------------
{
   // last = index of the last item in the subarray of
   // items yet to be sorted,
   // largest = index of the largest item found
   for (int last = n-1; last >= 1; --last)
   {  // Invariant: theArray[last+1..n-1] is sorted and
      // > theArray[0..last]

      // select largest item in theArray[0..last]
      int largest = indexOfLargest(theArray, last+1, c_count) ;

      // swap largest item theArray[largest] with
      // theArray[last]
      swap(theArray[largest], theArray[last]) ;
	 m_count += 3 ;
   } // end for
} // end selectionSort
