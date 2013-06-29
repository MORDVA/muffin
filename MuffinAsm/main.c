/*  Muffin Assembler
//
//  This is the source code for the muffin assember.
//  These are some basic regulations:

    Commands       |       Code         |       Token Amount
    ---------------------------------------------------------
    load                    0001                     2
    halt                    0000                     0
    mov                     0002                     2
    add                     0003                     3
    jmp                     0004                     1
    lbl                     0005                     1
    sub                     0006                     3

    => Scalar values begin with #
    => Register values begin with %

        -> Register names are one letter long
        -> if they are specified in lowercase (%a), they are automatically converted to uppercase (%A)
        -> the letters are encoded as decimal numbers (65 thru 90)

    => Memory addresses begin with @

    => mov destination, source


    ===================================
        ENCODING OF INSTRUCTIONS
    ===================================

    =>  Instruction encoding

        However, first a binary version of the instruction is created:

        EXAMPLE:

          0001         0000        0110           0100

        command       register    register       register
          code          code        code           code
                         or          or             or
                    label value                   value

//
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "usefulstring.h"

/* ======= FUNCTION PROTOTYPES ======== */

void assemble(char* pathOfFile);
void writeOutput(char* destinationPath);
void translate();

void extractScaler(char* token, char* binaryInstructions[]);

/* ============== GLOBALS ============= */

/* TODO: Dynamically allocate this array based on the number of lines in the file */

char* eachOutputLine[100]; /* Holds the assembly input code line by line */
char* eachInputLine[100];  /* Holds the binary output code line by line  */

/* TODO: Dynamically allocate this output code character array based on 16 * numOfLines */

char outputCode[100];

char* outputCodeString = outputCode;

int numberOfLines;

int main ( int argc, char *argv[] )
{
    printf("Muffin Assembler\n");

    if(argc == 2)
    {

        printf("\nBegin the assembly of %s", argv[1]);
        assemble(argv[1]);
        translate();
        writeOutput(argv[2]);

    }

    return 0;
}

void assemble(char* pathOfFile)
{

    /* Loop Counter */
    int i = 0;

    /* For the string tokenizer function */
    char * tokenPointer;

    /* The contents of the file */
    char * buffer = 0;

    /* The length of the file */
    long length;

    /* The file pointer */
    FILE * f = fopen (pathOfFile, "rb");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }

    if (buffer)
    {
        /* Data proccessing */

        printf("\nRecieved File:\n%s\n",buffer);

        /* Begin the proccess of splitting up all the strings into seperate commands */

        tokenPointer = strtok(buffer,"\n");

        while (tokenPointer != NULL)
        {
            eachInputLine[i] = tokenPointer;
            tokenPointer = strtok (NULL, "\n");
            i++;
        }

        numberOfLines = i;

    }


}

void writeOutput(char* destinationPath)
{

    printf("\nThis is the output generated and written: TODO\n");

}

void translate()
{

    int i;    /* Loop counting variables */
    int g;
    int z;

    /* The binary instruction array */
    char* binaryInstruction[4] = {"0000","0000","0000","0000"};

    /* The converted binary line */
    char bufferForLine[20];
    char* lineInBinary = bufferForLine;

    /* Used for splitting the current assembly line into tokens */
    char* tokenPointer;
    char* eachToken[4];

    /* A temporary buffer. Use when nessacary but remember to clear afterwords */

    char tempBuffer[4];

    /* Scan through each line of assembly */

    for(i = 0; i < numberOfLines; i++)
    {

        g = 0;

        /** Begin by splitting the current command into tokens */

        tokenPointer = strtok(eachInputLine[i]," ,;");

        while (tokenPointer != NULL)
        {
            eachToken[g] = tokenPointer;
            tokenPointer = strtok (NULL, ", ;");
            g++;
        }

        /* print out the tokens */

        printf("\nThe tokens for line %d:\n", i + 1);
        for(z = 0; z < 4; z++)
        {
            printf("\t%s\n",eachToken[z]);
        }

        /** First determine the command and encode it */

        if(strstr(eachToken[0],"mov") != NULL)
        {
            printf("Found a MOV command.\n");
            binaryInstruction[0] = "0002";

            /* Determine the register destination to encode*/

            if(strstr(eachToken[1],"%") != NULL){

                char stuff[20] = "0000";
                char* ptrstuff = stuff;

                sprintf(ptrstuff, "00%d",(int)toupper(*(strstr(eachToken[1],"%") + 1)));
                binaryInstruction[1] = ptrstuff;

                /* Determine the register source */

                char stuff2[20] = "0000";
                char* ptrstuff2 = stuff2;

                sprintf(ptrstuff2, "00%d",(int)toupper(*(strstr(eachToken[2],"%") + 1)));
                binaryInstruction[2] = ptrstuff2;

            }else{
                fprintf(stderr, "Error on line %d. No register present.", i);
                exit(0);
            }

        }

        else if(strstr(eachToken[0],"halt") != NULL)
        {
            printf("Found a HALT command.\n");
            binaryInstruction[0] = "0000";
        }

        else if(strstr(eachToken[0],"load") != NULL)
        {
            printf("Found a LOAD command.\n");
            binaryInstruction[0] = "0001";

            /* Determine the register to load to */

            if(strstr(eachToken[1],"%") != NULL){

                /* Encode the register */

                if(toupper(*(strstr(eachToken[1],"%") + 1)) == 'K'){

                    printf("K register is being loaded\n");
                    binaryInstruction[1] = "0075";

                }/** TODO: ADD MORE REGISTERS*/

                /* Encode the scaler value if present */

                if(strstr(eachToken[2],"#") != NULL){

                    extractScaler(eachToken[2],binaryInstruction);

                }


            }else{
                fprintf(stderr, "Error on line %d. No register present.", i);
                exit(0);
            }
        }
        /** Push the binary instruction */

        sprintf(lineInBinary, "%s%s%s%s\n", binaryInstruction[0],binaryInstruction[1],binaryInstruction[2],binaryInstruction[3]);

        printf("\nHere is the binary instruction pushed: %s",lineInBinary);

        /* Push the line into the output lines array */

        eachOutputLine[i] = lineInBinary;

        /* Flush the binary instruction */

        binaryInstruction[0] = "0000";
        binaryInstruction[1] = "0000";
        binaryInstruction[2] = "0000";
        binaryInstruction[3] = "0000";

        /* Flush the tokens for the line */

        eachToken[0] = "";
        eachToken[1] = "";
        eachToken[2] = "";
        eachToken[3] = "";

    }





}

/** extractScaler() function
//      Utilized for building scaler tokens.
//      Takes care of all sizing issues.
*/

void extractScaler(char* token, char* binaryInstructions[])
{

    char padding[10];
    char* ptrpadding;
    int i;

    token = token + 1;

    /* If the number is 4 or less digits in length */

    if(strlen(token) < 4){

        /* Add some padding zeroes */

        for(i = 0; i < (4 - strlen(token)); i++){

            padding[i] = '0';

        }

        padding[i] = '\0';

        ptrpadding = padding;

        // printf("Padding generated: %s", ptrpadding);

        prepend(token,ptrpadding);

        binaryInstructions[3] = token;

    }else if(strlen(token) == 4){

        binaryInstructions[3] = token;

    }else{

        /* TODO: ADD ENCODING HANDLING FOR NUMBERS WITH GREATER THAN 4 DIGITS */

    }


}

