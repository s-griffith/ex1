#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream) {
    RLEList head = NULL;
    head = RLEListCreate();
    if ((!in_stream) || (!head)) {
        return NULL;
    }
    char tempCharacter = '\0';
    while (!feof(in_stream)) {
        tempCharacter = fgetc(in_stream);
        if (RLEListAppend(head, tempCharacter) != RLE_LIST_SUCCESS) {
            return NULL;
        }
    }
    return head;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if ((!out_stream) || (!list)) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    char tempCharacter = '\0';
    RLEListResult result = RLE_LIST_SUCCESS;
    for (int i = 0; i < size - 1; i++) {
        tempCharacter = RLEListGet(list, i, &result);
        if (result != RLE_LIST_SUCCESS) {
            if (result == RLE_LIST_INDEX_OUT_OF_BOUNDS) {
                return RLE_LIST_ERROR;
            }
            return result;
        }
        fputc(tempCharacter, out_stream);
    }
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result = RLE_LIST_SUCCESS;
    char* outputString = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }
    char* tempString = outputString;
    while (*(tempString+3)) {
        fputc(*tempString, out_stream);
        tempString++;
    }
    free(outputString);
    return RLE_LIST_SUCCESS;
}