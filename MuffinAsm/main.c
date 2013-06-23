/*  Muffin Assembler
//
//  This is the source code for the muffin assember.
//  These are some basic regulations:

    Commands       |       Code         |       Token Amount
    ---------------------------------------------------------
    load                    1                        2
    halt                    0                        0
    mov                     2                        2
    add                     3                        3
    jmp                     4                        1
    lbl                     5                        1


    => Scalar values begin with #
    => Register values begin with %
    => Memory addresses begin with @

    => mov destination, source


    ===================================
        ENCODING OF INSTRUCTIONS
    ===================================

    =>  Instruction encoding is done with 4 numbers

    =>  The first number is the command code.

    =>  The second number is the the value of the token.

        -> This could be the number of the register
        -> This could be an address

    =>  The last two numbers can represent scalar values or two
        registers that need to be added.

//
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION PROTOTYPES

void assemble(char* pathOfFile);
void writeOutput();

// Globals

char * tokenPointer;

/* TODO: Dynamically allocate this array */
char * eachLine[100];

int main ( int argc, char *argv[] )
{
    printf("Muffin Assembler\n");

    if(argc == 2){

        printf("\nBegin the assembly of %s", argv[1]);
        assemble(argv[1]);

    }

    return 0;
}

void assemble(char* pathOfFile){

    /* Loop Counter */
    int i = 0;

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
        // Data proccessing
        printf("\nRecieved File:\n%s\n",buffer);

        // Begin the proccess of splitting up all the strings into seperate commands

        tokenPointer = strtok(buffer,"\n");

        while (tokenPointer != NULL)
        {
            eachLine[i] = tokenPointer;
            tokenPointer = strtok (NULL, "\n");
            i++;
        }

        printf("\nThis is the second line: %s", eachLine[1]);

    }


}

void writeOutput(){



}
