/*
Name: Stefan Suarez
Project Name: CS3100 Prog 5
Current Status: DONE
Description: Hash Table with
external linking collision handling
for social security numbers.
*/


#include <cmath>
#include "TableHash.h"


using namespace std ;

/*
Function Name: upCase
Purpose: Take care of case sensitivity issues in the program.
*/
void upCase(string& a1) {
  transform(a1.begin(), a1.end(), a1.begin(), (int (*)(int))toupper);
  return;
}

/*
Function Name: isPrime
Purpose: Return true if a number is prime. Else return false.
*/
bool isPrime(int numberToTest){
    bool noDivisorFound = true;
    double limit;
    limit = sqrt (numberToTest);
    int trialDivisor = 2;
    while ( noDivisorFound && (trialDivisor <= limit) )
    {
        if (numberToTest % trialDivisor == 0) {
            noDivisorFound = false;
        } else {
            ++trialDivisor;
        }
    }
    return noDivisorFound;
}

/*
Function Name: firstPrime
Purpose: Find the nearest prime greater than a given minimum.
*/
int firstPrime(int minVal){
    int primeCandidate = minVal;
    //Test the minVal for if it is prime
    while (!isPrime(primeCandidate)) {
        //If not, increment and test the new value
        ++primeCandidate;
        //Loop till finding the closest prime greater
        //than the min
    }
    return primeCandidate;
}

/*
Function Name: generateTableBorder
Purpose: Can call whenever I need to generate a border.
*/
void generateTableBorder(){
     cout << setfill('=') << setw(75) << "=" << endl;
}

/*
Function Name: Factorial
Purpose: Perform the factorial for the prediction
algorithm. Assumes the program only provides a positive,
whole number or 0.
*/
int Factorial(int Num){
    if (Num == 0) {
        return 1;
    } else {
        //Recursive call
        return Num * Factorial(Num - 1);
    }
}

/*
Function Name: countCollisions
Purpose: Calculate the actual number of slots that had items
hashed into them.
*/
int countCollisions(tableHash& currentTable, int testNumber) {
     int actualCollisions, tableSize, listLength;
     tableSize = currentTable.getLength();
     for (int i = 0; i < tableSize; ++i) {
         listLength = currentTable.getListLength(i);
         if (listLength == testNumber) {
             ++actualCollisions;
         }
     }
     return actualCollisions;
}

/*
Function Name: predictCollisions
Purpose: Calculate the predicted number of collisions
based on a given number of collisions(testNumber) for
a specific table(currentTable).
*/
double predictCollisions(tableHash& currentTable, int testNumber,
                      int numKeys) {
     //NEVER mix doubles with ints for calculations. It will break
     //this function in inexplicable ways.
     double Prediction, loadFactor, Numerator, kFact, tableSize;
     kFact = Factorial(testNumber);
     tableSize = currentTable.getLength();
     loadFactor = numKeys/tableSize;
     Numerator = 1/exp(loadFactor) * pow(loadFactor, testNumber);
     //Numerator/kFact = an efficiency number that needs to
     //be multiplied by the table size to find the number of
     //slots.
     Prediction = Numerator/kFact * tableSize;
     return Prediction;
}

/*
Function Name: printTabularReport
Purpose: Print out the Tabular Report findings
to common output. The calculuations are done in
separate functions.
*/
void printTabularReport(tableHash& currentTable, int numKeys) {
     int actualValue, roundedPercent, roundedPrediction;
     double percentDif, predictValue;
     cout << setw(16) << left << setfill(' ') << "Slot Count";
     cout << setw(16) << left << "Predicted";
     cout << setw(16) << left << "Actual";
     cout << setw(17) << left << "Act/Pred";
     cout << endl << endl;
     for(int i = 0; i < 6; ++i){
          cout << setw(16) << left << i;
          predictValue = predictCollisions(currentTable, i, numKeys);
          roundedPrediction = round(predictValue);
          cout << setw(16) << left << roundedPrediction;
          actualValue = countCollisions(currentTable, i);
          cout << setw(16) << left << actualValue;
          percentDif = actualValue/predictValue * 100;
          roundedPercent = round(percentDif);
          //If statement series to handle outputs too small
          //and too large.
          if (roundedPercent < 0.0001) {
               //If the percentage is smaller than 1/10000,
               //print INF to say it is too small
               cout << "INF";
          } else if (roundedPercent > 1000) {
               //When you divide a non-zero number by
               //zero, then cap the percentage at 1000
               //instead of displaying infinity.
               cout << "INF";
          } else {
               //In all other cases, you will have an actual percent
               //to output because the denominator will never be
               //zero with the efficiency algorithm.
               cout << roundedPercent << "%";
          }
          cout << endl;
     }
}

/*
Function Name: printRetrieveReport
Purpose: Separate calculations from output on
retrieve.
*/
void printRetrieveReport(bool& success, int& hashAddress, 
                         int& count, string& serialNum) {
     //This set-up for collumns reappears in other functions.
     //It is not the most effective for pre-known strings, but
     //I kept it in as a reminder that it works for strings.
     cout << setw(16) << left << setfill(' ') << "Key";
     cout << setw(16) << left << "Hash Address";
     cout << setw(16) << left << "Counter Value";
     cout << setw(17) << left << "Location in Table";
     cout << endl;
     cout << setw(16) << left << serialNum;
     if(success == true) {
          cout << setw(16) << left << hashAddress;
          cout << setw(16) << left << count;
          cout << hashAddress << endl;
     } else {
          cout << endl;
          cout << "NOT FOUND" << endl;
     }
     generateTableBorder();
}

/*
Function Name: printInsertionReport
Purpose: Separate calculations from output on
insertion.
*/
void printInsertionReport(bool& success, int& hashAddress, 
                         int& count, string& serialNum) {
     cout << setw(16) << left << setfill(' ') << "Key";
     cout << setw(16) << left << "Hash Address";
     cout << setw(16) << left << "Counter Value";
     cout << setw(17) << left << "Location in Table";
     cout << endl;
     cout << setw(16) << left << serialNum;
     if(success == true) {
          cout << setw(16) << left << hashAddress;
          cout << setw(16) << left << count;
          cout << hashAddress << endl;
     } else {
          cout << endl;
          cout << "DUPLICATE KEY OR TABLE FULL" << endl;
     }
     generateTableBorder();
}

/*
Function Name: printDeletionReport
Purpose: Separate calculations from output on
deletion.
*/
void printDeletionReport(bool& success, int& hashAddress, 
                         int& count, string& serialNum) {
     cout << setw(16) << left << setfill(' ') << "Key";
     cout << setw(16) << left << "Hash Address";
     cout << setw(16) << left << "Counter Value";
     cout << setw(17) << left << "Location in Table";
     cout << endl;
     cout << setw(16) << left << serialNum;
     if(success == true) {
          cout << setw(16) << left << hashAddress;
          cout << setw(16) << left << count;
          cout << hashAddress << endl;
     } else {
          cout << endl;
          cout << "KEY NOT PRESENT" << endl;
     }
     generateTableBorder();
}


/*
Function Name: retrieveSerial
Purpose: Perform necessary operations for a retrieve
so the program can print a report.
*/

void retrieveSerial(tableHash& currentTable, string& serialNum) {
     generateTableBorder();
     cout << "r " << serialNum << endl;
     cout << "RETRIEVE COMMAND" << endl << endl;
     bool success;
     int hashAddress, count;
     currentTable.hashRetrieve(serialNum, success, hashAddress);
     count = currentTable.getListLength(hashAddress);
     printRetrieveReport(success, hashAddress, count, serialNum);
}

/*
Function Name: insertSerial
Purpose: Perform necessary operations for an insertion
so the program can print a report.
*/
void insertSerial(tableHash& currentTable, string& serialNum) {
     generateTableBorder();
     cout << "i " << serialNum << endl;
     cout << "INSERT COMMAND" << endl << endl;
     bool success;
     int hashAddress, count;
     currentTable.hashInsert(serialNum, success, hashAddress);
     //Always find the count after an insert, because the list length
     //changes.
     count = currentTable.getListLength(hashAddress);
     printInsertionReport(success, hashAddress, count, serialNum);
}

/*
Function Name: deleteSerial
Purpose: Perform necessary operations for a deletion
so the program can print a report.
*/
void deleteSerial(tableHash& currentTable, string& serialNum) {
     generateTableBorder();
     cout << "d " << serialNum << endl;
     cout << "DELETE COMMAND" << endl << endl;
     bool success;
     int hashAddress, count;
     currentTable.hashDelete(serialNum, success, hashAddress);
     count = currentTable.getListLength(hashAddress);
     printDeletionReport(success, hashAddress, count, serialNum);
}

/*
Function Name: showTable
Purpose: Completely handles the show command by
calling the class method tableShow.
*/
void showTable(tableHash& currentTable) {
     generateTableBorder();
     cout << "s" << endl;
     cout << "SHOW COMMAND" << endl << endl;
     currentTable.tableShow();
     generateTableBorder();
}

/*
Function Name: quit
Purpose: Call the destructor and end the main
loop.
*/
void quit(tableHash& currentTable, bool& endLoop)
{
     generateTableBorder();
     cout << "q" << endl;
     cout << "QUIT COMMAND" << endl << endl;
     cout << "Now exiting. Goodbye." << endl;
     endLoop = true;
     generateTableBorder();
}

int main()
{
     //Throwaway vars for class method parameters
     int throwAwayHash;
     bool throwAwayBool;
     //
     //Assumption for simplicity: User will not try to break
     //the program
     int minTableSize, actualTableSize, numKeys;
     string currentSerial, command, parameterSerial;
     bool endLoop;
     cout << "Welcome to my social security, hashing experiment.";
     cout << endl;
     cout << "Please enter the minimum table size." << endl;
     cin >> minTableSize;
     actualTableSize = firstPrime(minTableSize);
	//Display actual table size given min table size
     cout << "Nearest Prime Size: " << actualTableSize << endl;
     tableHash serialTable(actualTableSize);
     cout << "Please enter the number of initial keys you wish to";
     cout << " hash." << endl;
     cin >> numKeys;
     cout << "Please enter the keys." << endl;
     for(int i = 0; i < numKeys; ++i){
          cin >> currentSerial;
          serialTable.hashInsert(currentSerial, throwAwayBool,
               throwAwayHash);
     }
     printTabularReport(serialTable, numKeys);
     cout << "You may now use the s, r, i, d, and q commands.";
     cout << endl;
     while (endLoop == false)
     {
          cin >> command;
          upCase(command);

          if(command == "S"){
               showTable(serialTable);
          } else if (command == "R") {
               cin >> parameterSerial;
               retrieveSerial(serialTable, parameterSerial);
          } else if (command == "I") {
               cin >> parameterSerial;
               insertSerial(serialTable, parameterSerial);
          } else if (command == "D") {
               cin >> parameterSerial;
               deleteSerial(serialTable, parameterSerial);
          } else if (command == "Q") {
               quit(serialTable, endLoop);
          } else {
          }
     }

     return 0 ;
     //default destructor called on serial table here
}
