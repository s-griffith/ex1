
#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream) {
    RLEList head = NULL;
    head = RLEListCreate();

    //If null arguments received or list not created
    if ((!in_stream) || (!head)) {
        return NULL;
    }

    //Initiate temporary variable for character
    char tempCharacter = '\0';

    //Compress the file
    while (!feof(in_stream)) {
        tempCharacter = fgetc(in_stream);
        if (RLEListAppend(head, tempCharacter) != RLE_LIST_SUCCESS) {
            return NULL;
        }
    }

    //Return the pointer to the linked list
    return head;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    //If null arguments received
    if ((!out_stream) || (!list)) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    File* tempFile = out_Stream;

    //Initiate variable for the size of the list, the current character and the pointer for the result error
    int size = RLEListSize(list);
    char tempCharacter = '\0';
    RLEListResult result = RLE_LIST_SUCCESS;
    //Decompress linked list to file
    for (int i = 0; i < size - 1; i++) {
        tempCharacter = RLEListGet(list, i, &result);
        if (result != RLE_LIST_SUCCESS) {
            if (result == RLE_LIST_INDEX_OUT_OF_BOUNDS) {
                return RLE_LIST_ERROR;
            }
            return result;
        }
        fputc(tempCharacter, tempFile);
    }
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result = RLE_LIST_SUCCESS;
    File* tempFile = out_Stream;
    char* outputString = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }
    char* tempString = outputString;
    while (*(outputString+3)) {
        fputc(*outputString, tempFile);
        outputString++;
    }
    free(tempString);
    return RLE_LIST_SUCCESS;
}