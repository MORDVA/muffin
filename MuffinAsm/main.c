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


    => Scalar values begin with #
    => Register values begin with %
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

/* ======= FUNCTION PROTOTYPES ======== */

void assemble(char* pathOfFile);
void writeOutput(char* destinationPath);
void translate();

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

    /* Scan through each line of assembly */

    for(i = 0; i < numberOfLines; i++)
    {

        g = 0;

        /* Begin by splitting the current command into tokens */

        tokenPointer = strtok(eachInputLine[i]," ,");

        while (tokenPointer != NULL)
        {
            eachToken[g] = tokenPointer;
            tokenPointer = strtok (NULL, ", ");
            g++;
        }

        /* print out the tokens */

        printf("\nThe tokens for line %d:\n", i + 1);
        for(z = 0; z < 4; z++)
        {
            printf("\t%s\n",eachToken[z]);
        }

        /* First determine the command and encode it */

        if(strstr(eachToken[0],"mov") != NULL)
        {
            printf("Found a MOV command.\n");
            binaryInstruction[0] = "0002";

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
        }
        /* Push the binary instruction */

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
