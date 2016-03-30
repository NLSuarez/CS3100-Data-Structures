//Note: When running sample ran1000 data,this function returns
//3 more compares than the sample text file states. Considered
//within the margin of error for now.

/* I furnished parameters c_count and m_count are here, for
   counting list element comparisons and list element moves. */

#include <iostream>

using namespace std;

void insertionSort(int theArray[ ], int n, 
                      unsigned long int & c_count, unsigned long int & m_count)
// ---------------------------------------------------
// Sorts the items in an array into ascending order.
// Precondition: theArray is an array of n items.
// Postcondition: theArray is sorted into ascending
// order; n is unchanged.
// ---------------------------------------------------
{
   // unsorted = first index of the unsorted region,
   // loc = index of insertion in the sorted region,
   // nextItem = next item in the unsorted region
   // initially, sorted region is theArray[0],
   // unsorted region is theArray[1..n-1];
   // in general, sorted region is
   // theArray[0..unsorted-1],
   // unsorted region is theArray[unsorted..n-1]

   for (int unsorted = 1; unsorted < n; ++unsorted)
   {  // Invariant: theArray[0..unsorted-1] is sorted

      // find the right position (loc) in
      // theArray[0..unsorted] for theArray[unsorted],
      // which is the first item in the unsorted
      // region; shift, if necessary, to make room
      int nextItem = theArray[unsorted];
      ++m_count; 
      int loc = unsorted;

/* Note: it is important that "++c_count" be performed below, rather than 
   "c_count++" The reason is that ++c_count will return "true"
    when c_count is zero, and c_count++ will not.  We need to
    "force" the comparison to be done after the increment. */

      for (;(loc > 0) && ++c_count &&  (theArray[loc-1 ]> nextItem); --loc)
	 // shift theArray[loc-1] to the right
      {
            theArray[loc] = theArray[loc-1];
            ++m_count;
      }
      // Assertion: theArray[loc] is where nextItem
      // belongs

      // insert nextItem into Sorted region
      theArray[loc] = nextItem;
      ++m_count ;
   } // end for
} // end insertionSort
