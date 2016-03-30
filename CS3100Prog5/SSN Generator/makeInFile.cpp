#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std ;

int main()
{
    /* initialize random number generator */
    srandom(time(NULL));
    //  srand(time(NULL)) ;
    int i, j, numKeys ;
    ofstream outFile ;
    string fName ;
    
    cout << "Enter the number of keys you want in your list: " ;
    cin >> numKeys ;
    cout << "Enter the name of the file to receive the list: " ;
    cin >> fName ;
    
    outFile.open(fName.c_str()) ;
    
    for (j=1; j<=numKeys; j++)
    {
        for (i=0; i<3; i++)  outFile << random()%10 ;
        outFile << '-' ;
        for (i=0; i<2; i++)  outFile << random()%10 ;
        outFile << '-' ;
        for (i=0; i<4; i++)  outFile << random()%10;
        
        //    if (j%6 == 0) outFile << endl ;
        //    else outFile << ' ' ;
        outFile << endl ;
        
    }
    outFile << endl ;
    return 0 ;
}



