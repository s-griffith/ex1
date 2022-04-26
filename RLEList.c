#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>

//------------------------Constants-------------------------------------
#define INVALID -1
#define NUM_OF_CATEGORIES 2
#define CONVERT_TO_ASCII 48
#define BASE_TEN 10
//----------------------------------------------------------------------


//------------------------Helper Functions------------------------------
int numOfDigits (RLEList list);
int translateToString (int appears, int index, char* string);
int numOfNodes (RLEList list);
void removeFirstNode(RLEList list);
//----------------------------------------------------------------------

struct RLEList_t{
    char symbol;
    int appears;
    RLEList next;
};

RLEList RLEListCreate() {
    RLEList node = (RLEList)malloc(sizeof(*node));
    if (!node) {
        return NULL;
    }
    node->symbol = '\0';
    node->appears = 0;
    node->next = NULL;
    return node;
}

void RLEListDestroy (RLEList list) {
    RLEList temp = list;
    while (!temp) {
        temp = list->next;
        free(list);
        list = temp;
    }
}

RLEListResult RLEListAppend (RLEList list, char value) {
    if (list == NULL)  {
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
    if (!list) {
        return INVALID;
    }
    int counter = 0;
    while (list != NULL) {
        counter += list->appears;
        list = list->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList current = list;
    RLEList previous = NULL;
    while ((current->appears <= index) && (current->next)) {
        index -= current->appears;
        previous = current;
        current = current->next;
    }
    if (current->appears > index) {
        if (current->appears == 1) {
            if (current != list) {
                if (!current->next) {
                    previous->next = NULL;
                }
                else if (previous->symbol == current->next->symbol) {
                    previous->appears += current->next->appears;
                    previous->next = current->next->next;
                    free(current->next);
                }
                else {
                    previous->next = current->next;
                }
            }
            else if (current->next) {
                current = list->next;
                removeFirstNode(list);
            }
            free(current);
        }
        else {
            current->appears -= 1;
        }
        return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if ((!list) && (result)) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    else if ((index < 0) && (result)) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else if ((list) && (index >= 0)) {
        RLEList current = list;
        while ((current->appears <= index) && (current->next)) {
            index -= current->appears;
            current = current->next;
        }
        if (current->appears > index) {
            if (result) {
                *result = RLE_LIST_SUCCESS;
            }
            return current->symbol;
        }
        if (result) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
    }
    return 0;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (list == NULL) {
        if (result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int size = numOfDigits(list) + (NUM_OF_CATEGORIES * numOfNodes(list)) + 1;
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

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if ((!list) || (!map_function)) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current = list;
    while (current) {
        current->symbol = map_function(current->symbol);
        current = current->next;
    }
    return RLE_LIST_SUCCESS;
}


//------------------------Helper Functions------------------------------

//Count the number of digits in the appearances of all the nodes of the linked list
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

//Convert integer number to string
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
        string[first] = string[index-i-1];
        string[index-i-1]  = temp;
    }
    return index; //the next open index in the string
}

//Count the number of nodes in the linked list
int numOfNodes (RLEList list) {
    int counter = 0;
    while (list != NULL) {
        counter++;
        list = list->next;
    }
    return counter;
}

//Remove the first node in the list by copying the second node into the first
void removeFirstNode(RLEList list) {
    list->appears = list->next->appears;
    list->symbol = list->next->symbol;
    list->next = list->next->next;
}