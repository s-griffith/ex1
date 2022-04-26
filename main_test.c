//
// Created by liorb on 18/04/2022.
//

#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>


int main() {

    //Testing Create-----------------------------------------------------------
    RLEList head = NULL;
    head = RLEListCreate();
    if (head == NULL) {
        return 0;
    }
    RLEListResult error;
    //-------------------------------------------------------------------------



    //Testing Size-------------------------------------------------------------
    int size = RLEListSize(head);
    if (size < 0) {
        printf("List is NULL in main\n");
        return 0;
    }
    printf("Current size: %d\n", size);
    printf("\n");
    //-------------------------------------------------------------------------



    //Testing Append-----------------------------------------------------------
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, 'b');
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, NULL);
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, 'a');
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'c');
    error = RLEListAppend(head, 'c');

    RLEListResult* result = (RLEListResult *)malloc(sizeof(*result));
    char* linkedList = RLEListExportToString(head, result);
    if (linkedList) {
        printf("Current list:\n%s\n", linkedList);
    }
    printf("\n");
    //-------------------------------------------------------------------------



    //Testing Size-------------------------------------------------------------
    size = RLEListSize(head);
    if (size < 0) {
        printf("List is NULL in main\n");
        return 0;
    }
    printf("Current size: %d\n", size);
    printf("\n");
    //-------------------------------------------------------------------------


    //Testing Get--------------------------------------------------------------
    printf("Get character at index 2, character: %c\n", RLEListGet(head,2, result));
    printf("Get character at index 0, character: %c\n", RLEListGet(head,0, result));
    printf("Get character at index 15, character: %c\n", RLEListGet(head,15, result));
    printf("Get character at index 34, character: %c\n", RLEListGet(head,34, result));
    printf("Get character at index -5, character: %c\n", RLEListGet(head,-5, result));
    printf("\n");
    //-------------------------------------------------------------------------


    //Testing Remove-----------------------------------------------------------
    error = RLEListRemove(head,2);
    printf("Removed index 2, error code: %d\n", error);
    linkedList = RLEListExportToString(head, result);
    if (linkedList) {
        printf("Current list:\n%s\n", linkedList);
    }

    error = RLEListRemove(head,20);
    printf("Removed index 20, error code: %d\n", error);
    linkedList = RLEListExportToString(head, result);
    if (linkedList) {
        printf("Current list: \n%s\n", linkedList);
    }

    error = RLEListRemove(head,0);
    printf("Removed index 0, error code: %d\n", error);
    linkedList = RLEListExportToString(head, result);
    if (linkedList) {
        printf("Current list:\n%s\n", linkedList);
    }

    error = RLEListRemove(head,13);
    printf("Removed index 13, error code: %d\n", error);
    linkedList = RLEListExportToString(head, result);
    if (linkedList) {
        printf("Current list:\n%s\n", linkedList);
    }

    error = RLEListRemove(head,2);
    printf("Removed index 2, error code: %d\n", error);
    linkedList = RLEListExportToString(head, result);
    if (linkedList) {
        printf("Current list:\n%s\n", linkedList);
    }
    printf("\n");
    //-------------------------------------------------------------------------



    //Testing Size-------------------------------------------------------------
    size = RLEListSize(head);
    if (size < 0) {
        printf("List is NULL in main\n");
        return 0;
    }
    printf("Current size: %d\n", size);
    printf("\n");
    //-------------------------------------------------------------------------


    //Freeing Resources--------------------------------------------------------
    free(linkedList);
    free(result);
    RLEListDestroy(head);
    //-------------------------------------------------------------------------

    return 0;
}








