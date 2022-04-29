#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>

//------------------------Constants-------------------------------------
#define INVALID -1
#define NUM_OF_CATEGORIES 2
#define CONVERT_TO_ASCII 48
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

//Creates the first node of a list.
RLEList RLEListCreate() 
{
    RLEList node = NULL;
    node = calloc(1, sizeof(*node));
    if (!node) {
        return NULL;
    }
    node->symbol = '\0';
    node->appears = 0;
    node->next = NULL;
    return node;
}

//Destroys the list.
void RLEListDestroy (RLEList list) 
{
    RLEList temp = list;
    while (temp) {
        temp = list->next;
        free(list);
        list = temp;
    }
}

//Increases appearances if the new symbol is identical to the previous symbol. Otherwise, adds a new node at the end.
RLEListResult RLEListAppend (RLEList list, char value) 
{
    if (!list)  {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (list->appears == 0) {
        list->symbol = value;
        list->appears++;
        return RLE_LIST_SUCCESS;
    }
    while (list->next) {
        list = list->next;
    }
    if (list->symbol == value) {
        list->appears++;
        return RLE_LIST_SUCCESS;
    }
    RLEList node = RLEListCreate();
    if (!node) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    node->symbol = value;
    node->appears++;
    list->next = node;
    return RLE_LIST_SUCCESS;
}

//Returns the number of characters the list represents.
int RLEListSize (RLEList list) 
{
    if (!list) {
        return INVALID;
    }
    int counter = 0;
    while (list) {
        counter += list->appears;
        list = list->next;
    }
    return counter;
}

//Removes node or character at a given index.
RLEListResult RLEListRemove(RLEList list, int index) 
{
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList current = list;
    RLEList previous = NULL;

    //Finds the requested index in the list. Saves the previous index for later use.
    while ((current->appears <= index) && (current->next)) {
        index -= current->appears;
        previous = current;
        current = current->next;
    }

    //Checks if the node needs to be removed entirely, or just decrease the appearances of the char.
    if (current->appears > index) {
        //The following happens when there is a necessity to remove an entire node.
        if (current->appears == 1) {
            //The following happens if the index does not belong to the first node of the list.
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
                free(current);
            }
            //This happens when the index belongs to the first node, but it is not the only node in the list.
            else if (current->next) {
                current = list->next;
                removeFirstNode(list);
                free(current);
            }
            //This happens when the index belongs to the one and only node of the list.
            else {
                current->appears = 0;
                current->symbol = '\0';
            }
        }
        else {
            current->appears -= 1;
        }
        return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

//Returns the character at a given index. If the character is not found for whatever reason, return 0.
char RLEListGet(RLEList list, int index, RLEListResult *result) 
{
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
    }
    else if ((index < 0) || ((list->appears == 0) && !(list->next))) {
        if (result) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
    }
    //If the index and list are both legitimate:
    else if ((list) && (index >= 0)) {
        RLEList current = list;
        //Finds the requested index.
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

//Translates the RLEList into a string in its compressed version.
char* RLEListExportToString(RLEList list, RLEListResult* result) 
{
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    //Adds 1 to the necessary size for the character '/0' at the end of the string
    int size = numOfDigits(list);
    size += (NUM_OF_CATEGORIES * numOfNodes(list)) + 1;
    char *string = (char*)malloc(sizeof(char)*size); //free! - by user
    if (!string) {
        if (result) {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    int index = 0;
    //Inputs the correct characters in the appropriate cells of the string.
    while (list) {
        string[index++] = list->symbol;
        index = translateToString(list->appears, index, string);
        string[index] = '\n';
        index++;
        list = list->next;
    }
    string[index] = '\0';
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return string;
 }

//Translates the list characters according to the given function.
RLEListResult RLEListMap(RLEList list, MapFunction map_function) 
{
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
int numOfDigits (RLEList list) 
{
    int appearsTemp = 0, counter = 0;
    RLEList current = list;
    while (current) {
        appearsTemp = current->appears;
        while (appearsTemp > 0) {
            appearsTemp /= 10;
            counter++;
        }
        current = current->next;
    }
    return counter;
}

//Convert integer number to string
int translateToString (int appears, int index, char* string) 
{
    int first = index;
    char temp = '\0';
    while (appears > 0) {
        string[index] = (appears % 10) + CONVERT_TO_ASCII;
        appears /= 10;
        index++;
    }
    for (int i = 0; i < (index - first)/2; i++) {
        temp = string[first + i];
        string[first + i] = string[index - i - 1];
        string[index - i - 1]  = temp;
    }
    //Returns the next open index in the string.
    return index;
}

//Count the number of nodes in the linked list
int numOfNodes (RLEList list) 
{
    int counter = 0;
    while (list) {
        counter++;
        list = list->next;
    }
    return counter;
}

//Copy the the second node into the first so the second node can be removed
void removeFirstNode(RLEList list) 
{
    list->appears = list->next->appears;
    list->symbol = list->next->symbol;
    list->next = list->next->next;
}