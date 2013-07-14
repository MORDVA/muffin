#include <stdio.h>
#include "globals.h"

/* PROTOTYPES */

void loadProg(char* srcFilePath);

/* GLOBALS */

char* programLines[99];  /* Holds each line of the program */
int jumpPoints[99];      /* Two parallel arrays*/
char *jumpNames[99];
int numberOfLines;

/* The registers */

typedef struct registers
{

} registerBank;

registerBank REGISTERS;

int main( int argc, char * argv[] )
{
    loadProg(argv[1]);
    return 0;
}

void loadProg(char* srcFilePath)
{

    printf("Executing %s\n", srcFilePath);

    /* Loads program into the memory */

    FILE *f = fopen(srcFilePath,"rb");

    /* Loop Counter */
    int i = 0;

    /* The contents of the file */
    char * buffer = 0;

    /* The length of the file */
    long length;

    /* A pointer to each line of the file */
    char* tokenPointer;

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
            programLines[i] = tokenPointer;
            tokenPointer = strtok (NULL, "\n");
            i++;
        }

        numberOfLines = i;

    }

}

/** Parses line by line to determine every jump point
*   Also sets instruction pointer to the start point
*/

void setPoints()
{


}

/** Scans through the jump names until a match is found
*   Then returns the parallel jumpPoints[] integer
*/

int getNewInstructionPointer(char* jumpName)
{

}

