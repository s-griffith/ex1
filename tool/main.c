#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//------------------------Global Variables------------------------------
#define FLAG 1
#define SOURCE 2
#define TARGET 3
#define INVERSION_SPACE ' '
#define INVERSION_AT '@'
#define NUM_OF_ARG 4
//----------------------------------------------------------------------


//------------------------Helper Function------------------------------

char invertAsciiArt(char inCharacter);

//----------------------------------------------------------------------


int main(int argc, char* argv[]) 
{
    //Checks that the main received the appropriate number of arguments.
    if ((argc < 3) || (argc > 4)) {
        return 0;
    }

    FILE* inStream = NULL;
    FILE* outStream = NULL;
    RLEListResult result = RLE_LIST_SUCCESS;
    //Checks that the function received a valid input file.
    if ((inStream = fopen(argv[SOURCE], "r")) != NULL) {
        //Checks that the function received an output file. If not, creates one with a default name.
        if (argv[TARGET] == NULL) {
            outStream = fopen("newOutput.txt", "w");
        }
        else {
            outStream = fopen(argv[TARGET], "w");
        }

        //Reads file and compress to RLE linked list
        RLEList head = asciiArtRead(inStream);
        //Decides what will happen based on the received flags.
        if (!strcmp(argv[FLAG],"-e")) {
            result = asciiArtPrintEncoded(head, outStream);
        }
        else if (!strcmp(argv[FLAG],"-i")) {
            if (RLEListMap(head, invertAsciiArt) == RLE_LIST_SUCCESS) {
                result = asciiArtPrint(head, outStream);
            }
        }
        //Frees dynamically allocated memory and opened files.
        RLEListDestroy(head);
        fclose(outStream);
        fclose(inStream);
    }
    if (result == 0) {
        return result;
    }
    return 0;
}


//-------------------------------------------------------------------------

/**
* invertAsciiArt: Changes all spaces to '@'
*
* The function maps characters to correct inversion
*
* @param inCharacter - The character that needs to be mapped
* @return
* 	If the input character is a space, then '@' is returned
* 	If the input is not a space, than the character is unchanged
*/
char invertAsciiArt(char inCharacter) 
{
    if (inCharacter == ' ') {
        return INVERSION_AT;
    }
    else if (inCharacter == '@') {
        return INVERSION_SPACE;
    }
    return inCharacter;
}