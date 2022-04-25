//
// Created by liorb on 19/04/2022.
//
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


//------------------------Helper Functions------------------------------

char invertAsciiArt(char inCharacter);

//----------------------------------------------------------------------


int main(int argc, char* argv[]) {
    if (argc != NUM_OF_ARG) {
        return 0;
    }

    FILE* inStream = fopen(argv[SOURCE], "r");
    FILE* outStream = fopen(argv[TARGET], "w");

    //Read file and compress to RLE linked list
    RLEList head = asciiArtRead(inStream);

    if (!strcmp(argv[FLAG],"-e")) {
        asciiArtPrintEncoded(head, outStream);
    }
    else if (!strcmp(argv[FLAG],"-i")) {
        if (RLEListMap(head, invertAsciiArt) == RLE_LIST_SUCCESS) {
            asciiArtPrint(head, outStream);
        }
    }

    //Releasing resources
    fclose(inStream);
    fclose(outStream);
    RLEListDestroy(head);

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
char invertAsciiArt(char inCharacter) {
    if (inCharacter == ' ') {
        return INVERSION_AT;
    }
    else if (inCharacter == '@') {
        return INVERSION_SPACE;
    }
    return inCharacter;
}