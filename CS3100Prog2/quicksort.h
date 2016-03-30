
/* I furnished parameters c_count and m_count are here, for
   counting list element comparisons and list element moves. */

void choosePivot(int theArray[ ], int first, int last) ;

void quicksort(int theArray[ ], int first, int last, 
                 unsigned long int & c_count, unsigned long int & m_count) ;

void partition(int theArray[ ], int first, int last, int &pivotIndex, 
                unsigned long int & c_count, unsigned long int & m_count);
