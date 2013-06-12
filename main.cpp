
// Include files

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

// Function prototypes

void flushRegisters();
void engine(string input);

/** GLOBAL VARIABLES and FAKE MEMORY!*/

// Stores the tokens and their type (initialized or not initialized)

vector <string> tokens;
vector <string> tokenType;

// Stores token value;

vector <int> tokenValInt;
vector <string> tokenValString;
vector <double> tokenValDouble;

// Memory for the interpreter

vector <int> intRegister;
vector <double> doubleRegister;
vector <string> stringRegister;

// Main function just for testing purposes

int main()
{
    string input;   // Stores current line the interpretter is working with

    while(1 == 1){

        cout << "$" << endl;
        getline(cin,input);
        engine(input);
    }


    return 0;
}

/**
/   FUNCTIONS DEALING WITH THE MEMORY!
/
*/

void flushRegisters(){

    intRegister.clear();
    doubleRegister.clear();
    stringRegister.clear();

}

/** THE ENGINE!!!
/
/
/
*/

void engine(string input){







}
