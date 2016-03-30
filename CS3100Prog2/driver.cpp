/*
Name: Stefan Suarez
Due Date: 9/29/2015
Description: Sort specified files with selection sort,
insertion sort, quicksort and mergesort; then output
a table showing how many compares and swaps were
executed during each sort.
*/

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include "selectionSort.h"
#include "insertionSort.h"
#include "quicksort.h"
#include "mergesort.h"

using namespace std;

/* Leave the declaration below commented out, because 
   MAX_SIZE is already defined in size.h,
   and size.h is included in mergesort.h,
   which is included here.

   However, _use_ MAX_SIZE as the size
   of all your data arrays.
*/
//const int MAX_SIZE = 50000 ;

int arrayCopy (int arrayA[], int arrayB[], int n) 
{
  // Attempted to find an already included way to assign arrays, but no dice.
  // I kept getting errors for half an hour.
  for(int idx=0; idx<n; idx++){
     arrayA[idx] = arrayB[idx];
  }

  return 0;
}

int main ()
{
  string fname, label, sortAgain ;
  ifstream inFile ; /* see pages 764-765 in Appendix G */
  int howMany, idx ;
  int A[MAX_SIZE] ; // declare all your data arrays to have MAX_SIZE
  int SortingA[MAX_SIZE] ;
  unsigned long countA[MAX_SIZE];
  unsigned long dataComps = 0, dataMoves = 0, sComps = 0, 
  sMoves = 0, iComps = 0, iMoves = 0, qComps = 0, qMoves = 0,
  mComps = 0, mMoves = 0 ;
 
      /* What follows should help you understand how to do the 
         I/O you need to do. */
  while(sortAgain != "n") {
   cout << "Enter Filename: " ;
   cin >> fname ; 

/* I'm not sure where in the book you find mention of the use of
   the "c_str()" method, but you need it here, if fname is a C++ string.
   The reason is that inFile.open expects an old-style C-string
   as the parameter.  Old style C-strings are arrays of characters
   that use a null character as an end-of-string marker. The "c_str()" 
   method converts a C++ string into a C-string. */

   inFile.open(fname.c_str()) ;  

/* Note that to get the label, it makes sense to read an entire line 
  as one string -- and the line will include spaces.  Usually white 
  space is taken as marking the end of a string. 
  Getline works in this situation. It inputs ALL characters, up to the
  end of the line (eol). Getline is mentioned on the bottom of page 710.  
  It will not put the eol character at the end of the label string.
  However getline will move past the eol in inFile, so that the next
  read done from inFile will be from the beginning of the next line. */

   getline (inFile, label) ; /* see page 710 */

   inFile >> howMany ;
   for (idx=0; idx<howMany; idx++)
   {
     inFile >> A[idx] ;
   }
   inFile.close() ;

   arrayCopy (SortingA, A, howMany) ;
   cout << "File Chosen: " << fname << endl ;
   cout << label << endl ;

   // Selection sort
   cout << "Selection sort starting ..." ;
   cout.flush() ;
   selectionSort(SortingA, howMany, dataComps, dataMoves) ;
   sComps = dataComps ;
   sMoves = dataMoves ;
   dataComps = 0 ;
   dataMoves = 0 ;
   cout << "done." << endl ;
   // Insertion sort
   arrayCopy (SortingA, A, howMany) ;
   cout << "Insertion sort starting ..." ;
   cout.flush() ;
   insertionSort(SortingA, howMany, dataComps, dataMoves) ;
   iComps = dataComps ;
   iMoves = dataMoves ;
   dataComps = 0 ;
   dataMoves = 0 ;
   cout << "done." << endl ;
   // Quick sort
   arrayCopy (SortingA, A, howMany) ;
   cout << "Quick sort starting ..." ;
   cout.flush() ;
   quicksort(SortingA, 0, howMany-1, dataComps, dataMoves) ;
   qComps = dataComps ;
   qMoves = dataMoves ;
   dataComps = 0 ;
   dataMoves = 0 ;
   cout << "done." << endl ;
   // Merge sort
   arrayCopy (SortingA, A, howMany) ;
   cout << "Merge sort starting ..." ;
   cout.flush() ;
   mergesort(SortingA, 0, howMany-1, dataComps, dataMoves) ;
   mComps = dataComps ;
   mMoves = dataMoves ;
   dataComps = 0 ;
   dataMoves = 0 ;
   cout << "done." << endl ;

   // Put a space between the processes and results.
   cout << endl << endl;

  
   // Use this block to generate the table when all sorts are done.
   cout << "The results of the sorts are as follows:" << endl ;
   cout << endl << endl ;
   cout << setw(40) << right ;
   cout <<"Compares       Moves" << endl ;
   cout << setw(18) << left << "Selection Sort:";
   cout << setw(10) << right << sComps << setw(12) << sMoves << endl ;
   cout << setw(18) << left << "Insertion Sort:";
   cout << setw(10) << right << iComps << setw(12) << iMoves << endl ;
   cout << setw(18) << left << "Quick Sort:";
   cout << setw(10) << right << qComps << setw(12) << qMoves << endl ;
   cout << setw(18) << left << "Merge Sort:";
   cout << setw(10) << right << mComps << setw(12) << mMoves << endl ;
   cout << endl << endl;


/*  selectionSort(A, howMany, dataComps, dataMoves) ; */
//  insertionSort(A, howMany, dataComps, dataMoves) ;  
           /* note difference in how these sort functions are called */
/*  quicksort(A, 0, howMany-1, dataComps, dataMoves) ; */
/*  mergesort(A, 0, howMany-1, dataComps, dataMoves) ; */  
   
   /*Include the following only if you want to see the sorted list
   cout << "Sorted list:" << endl ;
   for (idx=0; idx<howMany; idx++)
   {
        // See page 696 for some discussion of setw(), the field width 
           manipulator.  You will probably want to use it when you code
           the part of your program that writes the counts to the user's
           screen.
      cout << setw(9) << SortingA[idx] ; 
      if ((idx+1)%6 == 0) cout << endl ;
      else cout << ' ' ;
   }
   */
   cout << endl << endl ;

   cout << "Would you like to continue? (y/n):" << endl ;

   cin >> sortAgain ;
   //Unidentified reason for needing this. The while loop would
   //not terminate without it.
   if(sortAgain == "n"){
     break;
   }
  }
  cout << "Good bye." << endl ;

   return 0 ;
}
