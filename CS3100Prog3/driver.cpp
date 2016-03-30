/*
 Name: Stefan Suarez
 Last Date Worked On: 10/27/15
 Current Status: 
 DONE
 Objective: Create a basic database
 and inquiry system for criminals using
 a .txt file and the command line.
*/

#include <iostream>
#include <fstream>
#include <algorithm>

#include "ListP.h"
#include "BST.h" // binary tree operations

using namespace std;

/*
Function Name: upCase
Purpose: Since I used the transform
command a lot in this program, I decided
to make the conversion shorter by calling
it as a function.
*/
void upCase(string& a1)
{
  //Do not remove the typecast. The function will break without it.
  transform(a1.begin(), a1.end(), a1.begin(), (int (*)(int))toupper);
}

/*
Function Name: countRemainingSuspects
Purpose: To be used with each loop of the inquiry
function to determine if a tip eliminated all
suspects or if it left one suspect.
*/
void countRemainingSuspects(TreeItemType& person, int& suspects)
{
  if(person.isSuspect)
  {
    ++suspects;
  }
}

/*
Function Name: saveVisit
Purpose: Visit function to be used
with quit for saving each node.
*/
void saveVisit(TreeItemType& suspect, ofstream& stream)
{
  string a_string, keyName;
  keyName = suspect.getKey();
  upCase(keyName);
  int numberofAttr = suspect.attributes.getLength();
  //increment number of attributes for loop condition
  ++numberofAttr;
  stream << "Name:" << endl;
  stream << keyName << endl;
  stream << "Attributes:" << endl;
  for(int i = 1; i<numberofAttr; ++i){
    suspect.attributes.retrieve(i, a_string);
    upCase(a_string);
    stream << a_string << endl;
  }
  stream << "$" << endl;
  return;
}

/*
Function Name: tipVisit
Purpose: Visit function to be used
with TIP for checking attributes.
*/
void tipVisit(TreeItemType& person, string tip)
{
  string attr;
  bool stillSuspect = false;
  int numberofAttr = person.attributes.getLength();
  //increment number of attributes for loop condition
  ++numberofAttr;
  if(person.isSuspect)
  {
    for(int i = 1; i<numberofAttr; ++i){
      person.attributes.retrieve(i, attr);
      if(attr == tip)
      {
        //check all attributes
           //if you find one that matches the tip
           //flag this person as still a suspect
        stillSuspect = true;
      }
    }
      //if you iterate through all the attributes
        //of a suspect and still have a negative case
        //, then mark that person as not a suspect
    if(stillSuspect == false)
    {
      person.isSuspect = false;
    }
  }
  return;
}

/*
Function Name: printVisit
Purpose: Visit function to be used
with PRINT for printing out remaining
suspects in a tree.
*/
void printVisit(TreeItemType& suspect)
{
  if(suspect.isSuspect){
    cout << suspect.getKey() << endl;
  }
  return;
}


/*
Function Name: Quit
Purpose: to quit the program and save
changes to character.txt if changes were
made.
Pre-condition: Save function defined
*/
int QUIT(BinarySearchTree& tree)
{
  cout << "Saving data to 'character.txt'...";
  cout.flush();
  //predefined file name
  string fname = "character.txt";
  ofstream outFile;
  //Always include the trunc argument to erase what is
    //already in the file. Not doing so causes extra
    //output that breaks the program on the next run.
  outFile.open(fname.c_str(), ofstream::trunc) ;
  tree.saveTree(saveVisit, outFile);
  outFile.close();
  cout << "Data saved. Logging you out." << endl;
  cout << endl;
  return 0;
}

/*
Function Name: Add
Purpose: to add records to the bst suspects
database.
*/
int ADD(BinarySearchTree& tree)
{
  string criminalname, attribute;
  bool endLoop = false;
  List criminalattributes;
  int attributenumber;
  attributenumber = 1;
  cout << "Now adding criminal to database." << endl;
  cout << endl;
  cout << "Name of new Criminal:" << endl;
  getline(cin, criminalname);
  //Capitalize name for entry.
  upCase(criminalname);
  //Criminal name is there and 30 chars or less.
  if(criminalname.length() > 0 && criminalname.length() < 31){
    cout << endl;
    cout << "Attributes of new suspect:" << endl;
    while(endLoop == false){
      getline(cin, attribute);
      //If user did not hit enter twice.
      if(attribute.length() > 0){
        //If attribute is 30 chars or less
        if(attribute.length() < 31){
          //Capitalize each attribute.
          upCase(attribute);
          criminalattributes.insert(attributenumber, attribute);
          attributenumber++;
        } else {
          cout << "Your attribute is too long."
               << " Attributes can only be 30 characters or less."
               << endl;
        }
      } else {
        endLoop = true;
      }
    }
    KeyedItem CriminalID(criminalname, criminalattributes, true) ;
    tree.searchTreeInsert(CriminalID) ;
    criminalattributes.removeAll();
    cout.flush();
    cout << endl;
    cout << "Criminal Added." << endl;
    cout << endl;
  } else {
    cout << "Invalid name entered."
         << " All names must be at least one character long," << endl;
    cout << "and no more than 30 characters long." << endl;
  }
  return 0;
}

/*
Function Name: TIP
Purpose: to narrow down potential suspects
during an inquiry
Restriction: Only useable in an inquiry
*/
void TIP(BinarySearchTree& tree)
{
  string tip;
  cout << endl;
  cout << "Enter Tip Info:" << endl;
  getline(cin, tip);
  //capitalize tip
  upCase(tip);
  tree.tipTraverse(tipVisit, tip);
  return;
}

/*
Function Name: Check
Purpose: to check for a name in all keyed
items and see if it is still there.
Restriction: Only useable in an inquiry.
*/
void CHECK(BinarySearchTree& tree)
{
   string suspectName;
   KeyedItem Suspect;
   cout << "Enter Name of character:" << endl;
   getline(cin, suspectName);
   //Capitalize suspectName for case insensitive
    //comparison.
   upCase(suspectName);
   try {
     tree.searchTreeRetrieve(suspectName, Suspect);
       if (Suspect.isSuspect) {
           cout << suspectName << " is a suspect."
           << endl;
       } else {
           cout << suspectName << " is not a suspect."
           << endl;
       }
   } catch (TreeException) {
     cout << suspectName << " is not even in the database."
       << endl;
   }
   return;
}

/*
Function Name: Print
Purpose: Visit to print all remaining suspects
in-order.
Restriction: Only useable in an inquiry.
Pre-condition: printVisit() defined
*/
void PRINT(BinarySearchTree tree)
{
  int suspectsLeft = 0;
  tree.countSuspects(countRemainingSuspects, suspectsLeft);
  if (suspectsLeft == 0){
    cout << "There are currently no suspects." << endl;
  } else {
    cout << "The following suspects remain:" << endl;
    tree.inorderTraverse(printVisit);
    cout << endl;
  }
}

/*
Function Name: INQUIRY
Purpose: to begin a search for a suspect.
Allows the use of Tip, Check and Print
*/
string INQUIRY(BinarySearchTree tree)
{
    //Define loop and inquiry vars
    string sessionName, command, exitCommand;
    bool inquiryEnd = false;
    int suspectsLeft;
    //Initialize exitCommand to a specific value to
      //be read by the main function in case of
      //improper session name.
    exitCommand = "IMPROPER";
    //Make new tree and copy so I'm not constantly
      //referencing the tree.
    BinarySearchTree inquiryTree;
    inquiryTree = tree;
    //Begin prompting user
    cout << "Enter a name for this inquiry:" << endl;
    getline (cin, sessionName);
    //If sessionName is of appropriate length
    if(sessionName.length() > 0 & sessionName.length() < 31) {
      while (inquiryEnd == false){
        cout << "Now doing inquiry: " << sessionName;
        //line split because of character limit
        cout << ". You can use CHECK, PRINT or TIP." << endl;
        cout << "(ADD, INQUIRY or QUIT will break ";
        cout << "you out of the inquiry.)" << endl;
        cout << endl;
        getline (cin, command);
        upCase(command);
        if (command == "TIP") {
          TIP(inquiryTree);
          //Always reset suspectsLeft to 0 before calling
            //countSuspects because it is an incrementer.
          suspectsLeft = 0;
          inquiryTree.countSuspects(countRemainingSuspects, 
                   suspectsLeft);
          if(suspectsLeft == 1) {
            cout << "ALERT! That leaves only one" << endl;
            cout << "suspect in the " << sessionName;
            cout << " inquiry: ";
            //Since there's only one suspect, just call
              //the traverse function used in the PRINT
              //function.
            inquiryTree.inorderTraverse(printVisit);
          } else if (suspectsLeft == 0) {
            cout << "ALERT! That means there are no suspects" << endl;
            cout << "left in the " << sessionName;
            cout << " inquiry." << endl;
          }
        } else if (command == "CHECK"){
          CHECK(inquiryTree);
        } else if (command == "PRINT"){
          PRINT(inquiryTree);
        } else if (command == "ADD" | command == "INQUIRY"
                                  | command == "QUIT") {
            exitCommand = command;
            inquiryEnd = true;
            //destroy the inquiry tree to save memory
            inquiryTree.~BinarySearchTree();
            cout << endl;
            cout << "Ending inquiry: " << sessionName << endl;
            cout << endl;
        }
      }
    }
    return exitCommand;
}

/*
Function Name: UploadData
Purpose: to read records from the file
into a BST.
Preconditions: Character.txt is present
and in the proper format as follows -
Name:
<insert name>
Attribute:
<insert attribute list>
$
*/
int UploadData(BinarySearchTree& tree)
{
  string fname, currentitem, CriminalName ;
  bool endLoop;
  int attributeNumber ;
  List Attributes ;
  ifstream inFile ;
  attributeNumber = 1 ;
  fname = "character.txt";
  inFile.open(fname.c_str()) ;
  if(inFile.good()){
    while (inFile.peek() != EOF) {
      //reset endLoop at the beginning of each
         //item loop
      endLoop = false;
      //account for white space ahead of file marker
      inFile >> ws;
      getline (inFile, currentitem);
      if (currentitem == "Name:") {
        //if find a Name field, store
          //next line.
        inFile >> ws;
        getline (inFile, CriminalName);
        //next line should be attribute
          //field, so just bypass before
          //continuing.
        inFile >> ws;
        getline (inFile, currentitem);
        while (endLoop == false) {
          //Now, collect attributes till
          //you hit the delimiter.
          inFile >> ws;
          getline (inFile, currentitem);
          //Never remove this. Upload twice behavior
             //without it.
          if (currentitem != "$") {
            Attributes.insert(attributeNumber, currentitem);
            attributeNumber++ ;
          } else {
            endLoop = true;
          }
        }
        attributeNumber = 1;
      }
      //After finding all necessary information, put it into a keyed item.
      KeyedItem CriminalID(CriminalName, Attributes, true) ;
      //Insert item into the tree.
      tree.searchTreeInsert(CriminalID) ;
      //Clear the list for the next item
      Attributes.removeAll();
      //repeat
    }
  }
  inFile.close();
  return 0;
}


int main()
{
   string command, inquiryCommand;
   bool endLoop = false;
   bool returningFromInquiry = false;
   //Tree to be used for all functions
   BinarySearchTree Criminals;
   UploadData(Criminals);
   cout << "Welcome to CCD(Chaos Criminal Database)." << endl;
   while (endLoop == false)
   {
     //Don't ask for a command when returning
        //from an inquiry.
     if(returningFromInquiry != true){
       cout << endl;
       cout << "You are now in the main command loop.";
       cout << " ADD, INQUIRY and QUIT are available." << endl;
       cout << endl;
       getline (cin, command);
       upCase(command);
       cout << endl;
     }
     //Reset bool value after skipping command
       //input.
     returningFromInquiry = false;
     //ADD a criminal
     if(command == "ADD"){
       ADD(Criminals);
     } else if (command == "INQUIRY"){
       //Do an inquiry on a tree
       //Special syntax to account for the possibility
          //that a user entered an improper sessionName.
       //1. Collect returned inquiry command in its own string.
       inquiryCommand = INQUIRY(Criminals);
       //2. Test in inquiryCommand is IMPROPER
       if(inquiryCommand == "IMPROPER"){
         //3. If it is, print this message and return to main loop.
         cout << endl;
         cout << "Improper length for name of inquiry." << endl;
         cout << "All codenames must be no less than one";
         cout << " character and no more than 30 characters.";
         cout << endl << endl;
         cout << "Returning to MAIN LOOP" << endl;
	    cout << endl;
       } else {
         //4. If inquiryCommand is not IMPROPER, proceed normally.
         command = inquiryCommand;
         returningFromInquiry = true;
       }
     } else if (command == "QUIT"){
       //Save tree and exit program
       QUIT(Criminals);
       endLoop = true;
       //Destroy the tree
       Criminals.~BinarySearchTree();
     }
   }
  return 0;
} // end main