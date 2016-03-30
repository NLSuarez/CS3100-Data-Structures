// *********************************************************
// Header file TableHash.h for the ADT Hash Table with
// external linking for collision handling.
// Dynamic array implementation.
// *********************************************************

#ifndef TABLE_HASH
#define TABLE_HASH

#include <algorithm>
#include <iomanip>
#include "ListP.h"

using namespace std;

typedef listClass ItemType;

class tableHash
{
private:
// data field
ItemType *pa;	//pointer to first item in array
int SIZE;	//# of elements in array

public:
// constructors and destructor:
   tableHash();			//default constructor
   tableHash(int TableSize);  // parameterized constructor
   ~tableHash();              // destructor

// hash table operations:
   void hashInsert(string& serialNum, bool& success, int& desiredNum);
   void hashDelete(string& serialNum, bool& success, int& desiredNum);
   void hashRetrieve(string& serialNum, bool& success, 
        int& desiredNum);
   void tableShow() ;
   //Get the counter value for a specific item in the array
   int getListLength(int& hashAddress);
   int getLength() const;

protected:
//Hashing function
   int serialModHash(string serialNum);
//Sub function of hashing to remove hyphens in a string
   string removeHyphens(string serialNum);
}; // end class
// End of header file.

#endif