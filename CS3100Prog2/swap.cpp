// Assumes DataType has been defined

void swap(int &x, int &y)
// ---------------------------------------------------
// Swaps two items.
// Precondition: x and y are the items to be swapped.
// Postcondition: Contents of actual locations that x
// and y represent are swapped.
// ---------------------------------------------------
{
   int temp = x;
   x = y;
   y = temp;
} // end swap
