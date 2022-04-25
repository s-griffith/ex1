#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>
#define NUM_OF_CATEGORIES 2
#define CONVERT_TO_ASCII 48
#define BASE_TEN 10


RLEList findIndex (RLEList list, int index);
int translateToString (int appears, int index, char* string);
int numOfNodes (RLEList list);
int numOfDigits (RLEList list);

struct RLEList_t{
    char symbol;
    int appears;
    RLEList next;
};

RLEList RLEListCreate() {
    RLEList node = (RLEList)malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->appears = 0;
    node->next = NULL;
    return node;
}

void RLEListDestroy (RLEList list) {
    RLEList temp = list;
    while (temp != NULL) {
        temp = list->next;
        free(list);
        list = temp;
    }
}

RLEListResult RLEListAppend (RLEList list, char value) {
    if (list == NULL || value == NULL)  { //try inputting 0 as a scanf
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (list->appears == 0) {
        list->symbol = value;
        list->appears++;
        return RLE_LIST_SUCCESS;
    }
    while (list->next != NULL) {
        list = list->next;
    }
    if (list->symbol == value) {
        list->appears++;
        return RLE_LIST_SUCCESS;
    }
    RLEList node = RLEListCreate();
    if (node == NULL) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    node->symbol = value;
    node->appears++;
    list->next = node;
    return RLE_LIST_SUCCESS;
}

int RLEListSize (RLEList list) {
    if (list == NULL) {
        return -1;
    }
    int counter = 0;
    while (list != NULL) {
        counter += list->appears;
        list = list->next;
    }
    return counter;
}

//What happens where there's only one singular node? What if you want to destroy the first in a chain? What if you want to delete one of many inside a single node that is also the first/only?
RLEListResult RLEListRemove (RLEList list, int index) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index <= 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList previous = findIndex(list, index);
    if (previous == NULL) {
        previous = list;
 //       if (previous->next == NULL) {
 //           RLEListDestroy(list);
     //   }
    }
    RLEList delete = previous->next;
    if (delete == NULL) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if (delete->appears == 1) {
        previous->next=delete->next;
        delete->next = NULL;
        RLEListDestroy(delete);
    }
    else {
        list->appears--;
    }
    return RLE_LIST_SUCCESS;
    //if want to remove the last node? if there is only one node?
}

char RLEListGet (RLEList list, int index, RLEListResult *result) {
    if (list == NULL && result != NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    else if (index <= 0 && result != NULL) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else if (list != NULL && index > 0) {
        RLEList current = findIndex(list, index);
        if (current == NULL) {
            current == list;
        }
        else {
            current = current->next;
        }
        if (current == NULL && result != NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        else {
            if (result != NULL) {
                *result = RLE_LIST_SUCCESS;
            }
            return current->symbol;
        } 
    }
    return 0;
}

char* RLEListExportToString (RLEList list, RLEListResult* result) {
    if (list == NULL) {
        if (result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int size = numOfDigits(list) + NUM_OF_CATEGORIES*numOfNodes(list) + 1;
    char *string = (char*)malloc(sizeof(char)*size); //free! - by user
    if (string == NULL) {
        if (result != NULL) {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    int index = 0;
    while (list != NULL) {
        string[index++] = list->symbol;
        index = translateToString(list->appears, index, string);
        string[index] = '\n';
        index++;
        list = list->next;
    }
    string[index] = '\0';
    if (result != NULL) {
        *result = RLE_LIST_SUCCESS;
    }
    return string;
 }

RLEList findIndex (RLEList list, int index) {
    RLEList previous = NULL;
    while (list != NULL) {
        index -= list->appears;
        if(index <= 0) {
            break;
        }
        previous = list;
        list = list->next;
    }
    return previous;
 }

int numOfDigits (RLEList list) {
    int appearsTemp = 0, counter = 0;
    RLEList current = list;
    while (current) {
        appearsTemp = current->appears;
        while (appearsTemp > 0) {
            appearsTemp /= BASE_TEN;
            counter++;
        }
        current = current->next;
    }
    return counter;
}

int translateToString (int appears, int index, char* string) {
    int first = index;
    char temp;
    while (appears > 0) {
        string[index] = (appears % BASE_TEN) + CONVERT_TO_ASCII;
        appears /= BASE_TEN;
        index++;
    }
    for (int i = 0; i < (index-first)/2; i++) {
        temp = string[first+i];
        string[first] == string[index-i-1];
        string[index-i-1]  = temp;
    }
    return index; //the next open index in the string
}

int numOfNodes (RLEList list) {
    int counter = 0;
    while (list != NULL) {
        counter++;
        list = list->next;
    }
    return counter;
}