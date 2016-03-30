/*
        Creator Name: Stefan Suarez
        Informal Project Name: Expression Checker
        Description: This program will take user input and use a recursive function in order to test for the following, grammar rule -
                <expr> = S | I(C)T(<expr>)
*/

#include <iostream>
#include <string>

using namespace std;

bool isAnExpression (string str) ;

int main ()
{
        string testStr;
        cout << endl << endl << "The Expression Checker is running." ;
        cout << endl << endl ;

        while (cin >> testStr)
        {
			/* Future reference for what does not work to detect just plain carriage returns and line feeds:
				1. cin.get() breaks the whole thing.
				2. The following code just does not read. Preserved for future reference.
			if (testStr == '/r' | '/n' | '/r/n'){
				cout << "An empty string is obviously NOT an expression." << endl ;
			} */
			
			cout << testStr << endl;
               if (isAnExpression(testStr)) {
				cout << "The string IS an expression." << endl ;
			} else {
				cout << "The string IS NOT an expression." << endl ;
			}
        }
        cout << endl << endl << "Thank you for choosing Expression Checker 0.1." ;
        cout << endl << endl ;

        return 0 ;
}

/*Grammer Rule Review: <expr> = S | I(C)T(<expr>)*/
bool isAnExpression (string str)
{
        int len = str.length();
        string beginning = str.substr(0, 6);
        string ending = str.substr(len-1, 1);

        // Base Case: If the string is exactly 1 character, all we need to check for is an "S".
                if (len == 1)
                {
                        if (str == "S")
                                return true;
                        else return false;
                }
        // Normal Case: If the string is at least 8 characters long, check the beginning and the end for
        // the appropriate grammar. If they match, pass the sub string encapsulated by the beginning and end
        // strings through the function again for a recursive check. Otherwise, return false.
                else if (len > 7)
                {
                        if (beginning == "I(C)T(" && ending == ")")
                                return isAnExpression(str.substr(6, len-7));
                        else return false;
                }
        // Finally, return false in all other cases. This includes the base case of length < 1.
                else return false;
}
