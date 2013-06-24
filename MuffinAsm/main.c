/*  Muffin Assembler
//
//  This is the source code for the muffin assember.
//  These are some basic regulations:

    Commands       |       Code         |       Token Amount
    ---------------------------------------------------------
    load                    01                        2
    halt                    00                        0
    mov                     02                        2
    add                     03                        3
    jmp                     04                        1
    lbl                     05                        1


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

// FUNCTION PROTOTYPES

void assemble(char* pathOfFile);
void writeOutput(char* destinationPath);
void translate();

// Globals

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

    if(argc == 2){

        printf("\nBegin the assembly of %s", argv[1]);
        assemble(argv[1]);
        translate();
        writeOutput(argv[2]);

    }

    return 0;
}

void assemble(char* pathOfFile){

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
        // Data proccessing
        printf("\nRecieved File:\n%s\n",buffer);

        // Begin the proccess of splitting up all the strings into seperate commands

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

void writeOutput(char* destinationPath){

    printf("\nThis is the output generated and written: TODO\n");

}

void translate(){

    int i;
    int k;

    char* binaryInstruction[4] = {"0000","0000","0000","0000"};

    char bufferForLine[20];
    char* lineInBinary = bufferForLine;

    /* Scan through each line of assembly */

    for(i = 0; i < numberOfLines; i++)
    {

        /* First determine the command and encode it */

            // Scan through each character in the line of assembly

            for(k = 0; k < 10; k++){
                if((eachInputLine[i][k] == 'm') && (eachInputLine[i][k + 1] == 'o') && (eachInputLine[i][k + 2] == 'v')){
                    printf("\nMOV command found on line %d\n", i + 1);
                    break;
                }
            }



        /* Push the binary instruction */

        sprintf(lineInBinary, "%s%s%s%s\n", binaryInstruction[0],binaryInstruction[1],binaryInstruction[2],binaryInstruction[3]);

        printf("\nHere is the binary instruction pushed: %s",lineInBinary);

        // Put into global variable

        eachOutputLine[i] = lineInBinary;

        // Flush the binary instruction

        binaryInstruction[0] = "0000";
        binaryInstruction[1] = "0000";
        binaryInstruction[2] = "0000";
        binaryInstruction[3] = "0000";

    }





}
