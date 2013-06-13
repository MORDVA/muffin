
// Include files

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "ExpressionParser.h"

using namespace std;

// Function prototypes

void flushRegisters();
void engine(string input);
void flushSwitches();
void setSwitches(string input);
void courseOfAction(string input);

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

    // Initment switches

    bool initInt;
    bool initString;
    bool initDouble;

    // Assinment switch

    bool assignment;

    // Computation switch

    bool computation;

    // Lexer switches

    bool withinQoute;
    bool withinWhile;
    bool withinIf;

    /* HIGH LEVEL SWITCHES */

    bool rawComputation;

};

// Create instance of switchboard

switches switchBoard;

// Create an instance of the expression parser

ExpressionParser<int> parser;


// Create an instruction stack

vector <string> instructionStack;

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

    switchBoard.initInt = false;
    switchBoard.initString = false;
    switchBoard.initDouble = false;

    switchBoard.assignment = false;

    switchBoard.computation = false;
    switchBoard.withinQoute = false;
    switchBoard.withinWhile = false;
    switchBoard.withinIf = false;

    switchBoard.rawComputation = false;

}

/** THE ENGINE!!!
/
/
/
*/

void engine(string input){

    // Push back the instruction

    instructionStack.push_back(input);

    // Set switches

    setSwitches(input);

    courseOfAction(input);

    // Clear switches

    flushSwitches();

}

void setSwitches(string input){

    int i;

    // See what initment switches need to be set

    if(input.find("int ")!= string::npos){

        cout << "\nFOUND INTEGER INITIALIZATION\n";
        switchBoard.initInt = true;

    }

    if(input.find("double ")!= string::npos){

        cout << "\nFOUND DOUBLE INITIALIZATION\n";
        switchBoard.initDouble = true;

    }

    if(input.find("string ")!= string::npos){

        cout << "\nFOUND STRING INITIALIZATION\n";
        switchBoard.initString = true;

    }

    // Loop through input and determine what operator switches need to be set

    for(i = 0; i < input.size(); i++){

        if(input[i] == '='){
            switchBoard.assignment = true;
        }

        if(input[i] == '+' || input[i] == '-'||input[i] == '*'||input[i] == '%'){
            switchBoard.computation = true;
        }

    }

    // SET HIGH LEVEL SWITCHES

    if(switchBoard.computation == true && switchBoard.assignment == false){


        // Do the raw math problem

        /* EXTRA LOGIC GOES HERE TO REPLACE VARIABLES*/

        cout << "\n" << parser.eval(input) << "\n";

    }



}

void courseOfAction(string input){

    // Check the switchboard


}
