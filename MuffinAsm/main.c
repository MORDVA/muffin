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
void translate(char* destinationPath);
int gen_rand(void);

void extractScaler(char* token, char* binaryInstructions[]);

/* ============== GLOBALS ============= */

char* eachInputLine[99999999];  /* Holds the assembly input code line by line  */
int numberOfLines;              /* Holds the number of lines of assembly input code */

int main ( int argc, char *argv[] )
{
    printf("Muffin Assembler\n");

    if(argc == 3)
    {

        printf("\nAssembling %s", argv[1]);
        assemble(argv[1]);
        translate(argv[2]);

    }
    else
    {

        printf("\nError: Not enough arguments.\n");

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

        printf("\nRecieved File:\n====================================\n%s\n",buffer);

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

    printf("\n====================================");

}

void translate(char* destinationPath)
{

    int i;    /* Loop counting variables */
    int g;
    int z;
    int j = 0;
    int u;

    /* The binary instruction array */
    char* binaryInstruction[4] = {"XXXX","XXXX","XXXX","XXXX"};

    /* The converted binary line */
    char bufferForLine[20];
    char* lineInBinary = bufferForLine;

    /* Used for splitting the current assembly line into tokens */

    char* tokenPointer;
    char* eachToken[4];

    /* A temporary buffer. Use when nessacary but remember to clear afterwords */

    char tempBuffer[4];

    /* Two parallel arrays used for setting up labels */

    char* labelNames[9999];
    int* labelEncodings = (int*) malloc(sizeof(int) * 1);

    /* Open and set up the file output will be written to */

    FILE *dest;
    dest = fopen(destinationPath, "w");

    printf("\nWriting to %s\n",destinationPath);

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

        printf("\n==================================\nThe tokens for line %d:\n", i + 1);
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

            if(strstr(eachToken[1],"%") != NULL)
            {

                char tempEncoding[20] = "0000";
                char* ptrtempEncoding = tempEncoding;

                sprintf(ptrtempEncoding, "00%d",(int)toupper(*(strstr(eachToken[1],"%") + 1)));
                binaryInstruction[1] = ptrtempEncoding;

                /* Determine the register source */

                char tempEncoding2[20] = "0000";
                char* ptrtempEncoding2 = tempEncoding2;

                sprintf(ptrtempEncoding2, "00%d",(int)toupper(*(strstr(eachToken[2],"%") + 1)));
                binaryInstruction[2] = ptrtempEncoding2;

            }
            else
            {
                fprintf(stderr, "Error on line %d. No register present.", i);
                exit(0);
            }

        }

        else if(strstr(eachToken[0],"halt") != NULL)
        {
            printf("Found a HALT command.\n");
            binaryInstruction[0] = "0000";
        }

        else if(strstr(eachToken[0],"lbl") != NULL)
        {
            printf("Found a LBL command.\n");

            /* Encode the label */
            gen_rand();
            int numberGenerated = gen_rand();
            *labelEncodings = numberGenerated;

            /* Record the label name */
            labelNames[j] = eachToken[1];

            printf("Just found label: %s",labelNames[j]);

            /* Push the label */

            char strToPush[20] = "0000";
            sprintf(strToPush,"%d",*labelEncodings);

            binaryInstruction[0] = "0005";
            binaryInstruction[1] = strToPush;

            /* Increment and reallocate memory */

            j++;
            labelEncodings = (int*) realloc (labelEncodings, sizeof(int) * (j + 1));
            labelEncodings += j;


        }

        else if(strstr(eachToken[0],"jmp") != NULL)
        {
            printf("Found a JMP command.\n");
            printf("Just found jump point: %s", eachToken[1]);

            /* Find the jump name */
            /*for(u = 0; u < j; u++)
            {
                if(eachToken[1]){
                    printf("\nLegal Jump\n");
                    break;
                }
            }*/

            binaryInstruction[0] = "0004";
        }

        else if(strstr(eachToken[0],"load") != NULL)
        {
            printf("Found a LOAD command.\n");
            binaryInstruction[0] = "0001";

            /* Determine the register to load to */

            if(strstr(eachToken[1],"%") != NULL)
            {

                /* Encode the register */

                char tempEncoding3[20] = "0000";
                char* ptrtempEncoding3 = tempEncoding3;

                sprintf(ptrtempEncoding3, "00%d",(int)toupper(*(strstr(eachToken[1],"%") + 1)));

                printf("%c register is being loaded\n",toupper(*(strstr(eachToken[1],"%") + 1)));
                binaryInstruction[1] = ptrtempEncoding3;

                /* Encode the scaler value if present */

                if(strstr(eachToken[2],"#") != NULL)
                {

                    extractScaler(eachToken[2],binaryInstruction);

                }


            }
            else
            {
                fprintf(stderr, "Error on line %d. No register present.", i);
                exit(0);
            }
        }
        /** Push the binary instruction */

        sprintf(lineInBinary, "%s%s%s%s\n", binaryInstruction[0],binaryInstruction[1],binaryInstruction[2],binaryInstruction[3]);

        printf("\nHere is the binary instruction pushed: %s",lineInBinary);

        /* Write the line */

        fprintf(dest,"%s",lineInBinary);

        /* Flush the binary instruction */

        binaryInstruction[0] = "XXXX";
        binaryInstruction[1] = "XXXX";
        binaryInstruction[2] = "XXXX";
        binaryInstruction[3] = "XXXX";

        /* Flush the tokens for the line */

        eachToken[0] = "";
        eachToken[1] = "";
        eachToken[2] = "";
        eachToken[3] = "";

    }

    /* Close the output file */
    fclose(dest);

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

    if(strlen(token) < 4)
    {

        /* Add some padding zeroes */

        for(i = 0; i < (4 - strlen(token)); i++)
        {

            padding[i] = '0';

        }

        padding[i] = '\0';

        ptrpadding = padding;

        printf("\nPadding generated: %s", ptrpadding);

        prepend(token,ptrpadding);

        binaryInstructions[3] = token;

    }
    else if(strlen(token) == 4)
    {

        binaryInstructions[3] = token;

    }
    else
    {
        /* Add some padding zeroes */

        for(i = 0; i < (8 - strlen(token)); i++)
        {

            padding[i] = '0';

        }

        padding[i] = '\0';

        ptrpadding = padding;

        printf("Padding generated: %s", ptrpadding);

        prepend(token,ptrpadding);

        printf("Here is the greater than 4 digit string: %s", token);

        char firstHalf[40] = "0000";
        char secondHalf[40] = "0000";
        char* firstHalfPtr = firstHalf;
        char* secondHalfPtr = secondHalf;
        int y;

        for(y = 0; y < 4; y++)
        {
            firstHalf[y] = *token;
            token++;
        }

        firstHalf[y] = '\0';

        for(y = 0; y < 4; y++)
        {
            secondHalf[y] = *token;
            token++;
        }

        secondHalf[y] = '\0';

        printf("\nHere is the first half: %s",firstHalfPtr);
        printf("\nHere is the first half: %s",secondHalfPtr);

        binaryInstructions[2] = firstHalfPtr;
        binaryInstructions[3] = secondHalfPtr;
    }


}

/** Random number generation function
*   returns random number in range of 0 to 9999
*/

int gen_rand(void)
{
   int n;
   n= rand() % 10000;  /* n is random number in range of 0 - 99 */
   return n;
}


