#include "RLEList.h"
#include <stdlib.h>
#define NUM_OF_CATEGORIES 3

RLEList findIndex (RLEList list, int index);

struct RLEList_t{
    char symbol;
    int appears;
    RLEList next;
};

RLEList RLEListCreate() {
    RLEList node = malloc(sizeof(*node));
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
    if (list == NULL)  { //how do you check that value is not null? if you do value == NULL, it gives an error 
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
        list = list ->next;
    }
    return counter;
}

RLEListResult RLEListRemove (RLEList list, int index) {
    //Does the index count start at 1 or 0? From Piazza - search "remove"
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index <= 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    list = findIndex(list, index);
    if (list == NULL) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if (list->appears == 1) {
        RLEList temp =list->next;
        list->next=temp->next;
        temp->next = NULL;
        RLEListDestroy(temp);
    }
    else {
        list->appears--;
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet (RLEList list, int index, RLEListResult *result) { //if what is null the result will not be saved??
    if (list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    else if (index <= 0) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else {
        list = findIndex(list, index);
        if (list == NULL) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        *result = RLE_LIST_SUCCESS;
        return list->symbol;
    }
    return 0;
}

char* RLEListExportToString (RLEList list, RLEListResult* result) { //if what is null, the result won't be saved?
    if (list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int size = NUM_OF_CATEGORIES*RLEListSize(list)+1;
    char *string = malloc(sizeof(char)*size); //free! - by user
    if (string == NULL) {
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    int index = 0;
    while (list != NULL) {
        string[index] = list->symbol;
        string[++index] = list->appears;
        string[++index] = '\n';
        index++;
    }
    string[index] = '\0';
    *result = RLE_LIST_SUCCESS;
    return string;
 }

 RLEList findIndex (RLEList list, int index) {
    while (list != NULL) {
        index -= list->appears;
        if(index <= 0) {
            break;
        }
        list = list->next;
    }
    return list;
 }

