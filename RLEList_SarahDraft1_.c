#include "RLEList.h"
#define NUM_OF_CATEGORIES 3


struct RLEList_t{
    char symbol;
    RLEList next;
};

RLEList RLEListCreate() {
    RLEList node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
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
    if (value == NULL || list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList node = RLEListCreate();
    if (node == NULL) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    if (list->next == NULL) {
        list->symbol = value;
    }
    else {
        node->next = value;
        while (list != NULL) {
            list = list->next;
        }
        list->next = node;
    }
    return RLE_LIST_SUCCESS;
}

int RLEListSize (RLEList list) {
    if (list == NULL) {
        return -1;
    }
    int counter = 0;
    while (list != NULL) {
        counter++;
        list = list ->next;
    }
    return counter;
}

RLEListResult RLEListRemove (RLEList list, int index) {
    //Does the index count start at 1 or 0? From Piazza - search "remove"
    if (list == NULL ||  index == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index <= 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    for (int i = 1; i < index-1; i++) {
        if (list->next == NULL) {
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        list = list->next;
    }
    RLEList temp =list->next;
    list->next=temp->next;
    temp->next = NULL;
    RLEListDestroy(temp);
    return RLE_LIST_SUCCESS;
}

char RLEListGet (RLEList list, int index, RLEListResult *result) { //if what is null the result will not be saved??
    if (index == NULL || list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    else if (index <= 0) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else {
        for (int i = 1; i < index; i++) {
            if (list->next == NULL) {
                return RLE_LIST_INDEX_OUT_OF_BOUNDS;
            }
            list = list->next;
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
    int counter = 0;
    int size = NUM_OF_CATEGORIES*RLEListSize(list)+1;
    char *string = malloc(sizeof(char)*size); //free! - by user
    int index = 0;
    if (string == NULL) {
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    while (list != NULL) {
        if (list->symbol == list->next->symbol) {
            counter++;
            list = list->next;
            continue;
        }
        string[index] = list->symbol;
        string[++index] = counter;
        string[++index] = '\n';
        counter = 0;
        index++;
    }
    string[index] = '\0';
    *result = RLE_LIST_SUCCESS;
    return string;
 }
