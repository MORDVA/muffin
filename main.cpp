
// Include files

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

// Function prototypes

void flushRegisters();
void engine(string input);
void flushSwitches();
void setSwitches(string input);

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

// Switches

struct switches{

    bool assignment;
    bool initment;
    bool computation;
    bool withinParen;
    bool withinWhile;
    bool withinIf;

};

// Create instance of switchboard

switches switchBoard;


// Main function just for testing purposes

int main()
{
    string input;   // Stores current line the interpretter is working with

    while(1 == 1){

        cout << endl << "$" << endl;
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

void flushSwitches(){

    switchBoard.assignment = false;
    switchBoard.initment = false;
    switchBoard.withinIf = false;
    switchBoard.withinParen = false;
    switchBoard.withinWhile = false;

}

/** THE ENGINE!!!
/
/
/
*/

void engine(string input){

    // Set switches

    setSwitches(input);




    // Clear switches

    flushSwitches();

}

void setSwitches(string input){

    int i;

    // Loop through input and determine what switches need to be set

    for(i = 0; i < input.size(); i++){

        if(input[i] == '='){
            switchBoard.assignment = true;
        }

        if(input[i] == '+' || input[i] == '-'||input[i] == '*'||input[i] == '%'){
            switchBoard.computation = true;
        }

    }



}
