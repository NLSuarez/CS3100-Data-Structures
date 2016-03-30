// *********************************************************
// Implementation file TableHash.cpp for the ADT Hash Table 
// with external linking for collision handling.
// Dynamic array implementation.
// *********************************************************
#include "TableHash.h"

int tableHash::getLength() const{
     return SIZE;
}//end getLength

int tableHash::getListLength(int& hashAddress) {
     int count = pa[hashAddress].ListLength();
     return count;
}//end getListLength

tableHash::tableHash(){
     pa = nullptr;
}//end default constructor

tableHash::tableHash(int TableSize){
     SIZE = TableSize;
     pa = new ItemType[SIZE];
}//end parameterized constructor


tableHash::~tableHash(){
     delete [] pa;
}//end default destructor

/*
Name: hashInsert
Purpose: Given a serial number, hash into
the appropriate address in the table and feed
that hash address back to the main program.
*/
void tableHash::hashInsert(string& serialNum, bool& success,
                             int& desiredNum) {
     string unhashedSerial = serialNum;
     //Call the hash function for the formatted serial
     desiredNum = serialModHash(unhashedSerial);
     //The list insert function always extends the list length
     //by 1, so the new item is automatically tacked onto the
     //end of the list for convenience.
     int nextItem = pa[desiredNum].ListLength() + 1;
     //Now, is the item currently existing in the list?
     //Use a ListItemRetrieve to find out.
     //Boolean check for duplicates
     bool duplicateSerial;
     //Throwaway var.
     int position;

     pa[desiredNum].ListItemRetrieve(serialNum, duplicateSerial, position);

     if(duplicateSerial)
     {
          success = false;
     } else {
          pa[desiredNum].ListInsert(nextItem, serialNum, success);
     }
}

/*
Name: hashDelete
Purpose: Given a serial number, find it in the table
and delete it from the appropriate list. Also, feed
back the hash address for a printout.
*/
void tableHash::hashDelete(string& serialNum, bool& success,
                             int& desiredNum) {
     int position; //position where the serial num is located
     //Used with the deletion method in the list class.
     string unhashedSerial = serialNum;
     //As with insertion, find the appropriate address using the
     //has function.
     desiredNum = serialModHash(unhashedSerial);
     //Track down the position of the desired item at the appropraite
     //address for use with the included ListDelete method.
     pa[desiredNum].ListItemRetrieve(serialNum, success, position);
     if(success) {
          //If the number is there, delete it.
          pa[desiredNum].ListDelete(position, success);
     }
}

/*
Name: hashRetrieve
Purpose: Search for a serial in the hash table.
Reference back success and a hash address whether
it is found or not. The main program will handle
whether it is present or not.
*/
void tableHash::hashRetrieve(string& serialNum, bool& success,
                             int& desiredNum) {
     //Throwaway var. Only necessary for ListItemRetrieve
     //parameters.
     int position;
     string unhashedSerial = serialNum;
     desiredNum = serialModHash(unhashedSerial);
     pa[desiredNum].ListItemRetrieve(serialNum, success, position);
}

void tableHash::tableShow(){
     //Table header
     cout << "INDEX      VALUES" << endl;
     cout << endl;
     //Iterate through the whole table
     for(int i = 0; i < SIZE; ++i) {
          //If there is something hashed in a location.
          if(!pa[i].ListIsEmpty())
          {
               //Print the address
               cout << setw(7) << left << setfill(' ') << i;
               //Then print all items stored there
               pa[i].ListPrint();
               cout << endl;
          }
     }

}

/*
Name: serialModHash
Purpose: This is the hashing function that returns
an integer, hashing address. It does the
modulus operation necessary for finding an address.
It will also make sure to call another function to
change all serials are changed from strings to
9-digit integers.
*/
int tableHash::serialModHash(string serialNum){
     string unformatedSerial = serialNum;
     //First, remove the hyphens with another function.
     string formatedSerial = removeHyphens(unformatedSerial);
     //Now call atoi to transform the string into an integer
     int hashableNum = atoi(formatedSerial.c_str());
     //Next, modulus operation using table size and the serial
     int hashAddress = hashableNum % SIZE;
     //Finally, return the hash address.
     return hashAddress;
}

/*
Name: removeHyphens
Purpose: Given a regular, formatted serial number,
remove the hyphens so that the hashing function can
do its job.
*/
string tableHash::removeHyphens(string serialNum){
     string plainSerial = serialNum;
     //Define the character to remove.
     char extraHyphens = '-';
     //Next line requires the algorithm library
     //Will remove all the hyphens and also the white space
     //generated by that removal so an 11 digit string becomes
     //a 9 digit string.
     plainSerial.erase(remove(plainSerial.begin(), 
          plainSerial.end(), extraHyphens), plainSerial.end());
     //Return the new string.
     return plainSerial;
}

