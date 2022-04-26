
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

    //Initiate variable for the size of the list, the current character and the pointer for the result error
    int size = RLEListSize(list);
    char tempCharacter = '\0';
    RLEListResult* result = RLE_LIST_SUCCESS; //If doesn't work: RLEListResult* result = (RLEListResult*)malloc(sizeof(*result))
    if (!result) {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    //Decompress linked list to file
    for (int i = 0; i < size - 1; i++) {
        tempCharacter = RLEListGet(list, i, result);
        if (*result != RLE_LIST_SUCCESS) {
            return *result;
        }
        fputc(tempCharacter, out_stream);
    }

    //free(result);
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result = RLE_LIST_SUCCESS; //(RLEListResult*)malloc(sizeof(*result));
    if (!result) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    char* outputString = RLEListExportToString (list, result);
    if (*result != RLE_LIST_SUCCESS) {
        return *result; //need to only return RLE_NULL_ARGUMENT or RLE_LIST_SUCCESS?
    }
    while (outputString) {
        fputc(*outputString, out_stream);
        outputString++;
    }
    free(outputString);
    return RLE_LIST_SUCCESS;
}