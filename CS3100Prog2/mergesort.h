
/* I furnished parameters c_count and m_count are here, for
   counting list element comparisons and list element moves. */

#include "size.h"

void merge(int theArray[ ], int first, int mid, int last, 
             unsigned long int & c_count, unsigned long int & m_count) ;

void mergesort(int theArray[ ], int first, int last, 
                 unsigned long int & c_count, unsigned long int & m_count) ;
