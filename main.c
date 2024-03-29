#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

void testListCreate();
void testListCount();
void testListFirst();
void testListLast();
void testListNext();
void testListPrev();
void testListCurr();
void testListAppend();
void testListPrepend();
void testListInsertAfter();
void testListInsertBefore();
void testListRemove();
void testListTrim();
void testListConcat();
void testListFree();
void testListSearch();

void printList();
void addItemsToList();
void freeItem();
bool intComparator();

int main() 
{
    // testListCreate();
    
    // testListCount();
    
    // testListFirst();
    // testListLast();
    
    // testListNext();
    // testListPrev();
    // testListCurr();

    // testListAppend();
    // testListPrepend();

    // testListInsertAfter();
    // testListInsertBefore();

    // testListRemove();
    // testListTrim();
    
    // testListConcat();

    // testListFree();

    // testListSearch();
}

void testListCreate() 
{
    printf("Testing List_create...\n");
    
    // Test 1: Creating maximum number of lists
    List* lists[LIST_MAX_NUM_HEADS + 1]; 
    int i;
    for (i = 0; i < LIST_MAX_NUM_HEADS; i++) {
        lists[i] = List_create();
        if (lists[i] == NULL) {
            printf("Error: Failed to create list %d\n", i + 1);
            break;
        }
    }

    printf("%d lists were sucessfully created.\n", i);

    // Test creating 1 more list beyond the limit
    lists[LIST_MAX_NUM_HEADS] = List_create();
    if (lists[LIST_MAX_NUM_HEADS] == NULL) {
        printf("Passed: Unable to create a list beyond the maximum limit.\n");
    } else {
        printf("Failed: Should not be able to create more than %d lists.\n", LIST_MAX_NUM_HEADS);
    }
    
    printf("List_create tests completed.\n");
}

void testListCount() 
{
    printf("Testing List_count...\n");

    // Test 1: Count in an empty list
    List* testList = List_create();
    int count = List_count(testList);
    printf("Test 1 - Empty list count: %s\n", (count == 0) ? "Passed" : "Failed");

    // Test 2: Count in a list with 1 item
    int item1 = 10;
    List_append(testList, &item1);
    count = List_count(testList);
    printf("Test 2 - Single item list count: %s\n", (count == 1) ? "Passed" : "Failed");

    // Test 3: Count in a list with multiple items
    int item2 = 20;
    List_append(testList, &item2);
    count = List_count(testList);
    printf("Test 3 - Multiple items list count: %s\n", (count == 2) ? "Passed" : "Failed");

    printf("List_count tests completed.\n");
}

void testListFirst() 
{
    printf("Testing List_first...\n");

    // Test 1: List_first on an empty list
    List* testList = List_create();
    void* item = List_first(testList);
    printf("Test 1 - Empty list: %s\n", (item == NULL && List_curr(testList) == NULL) ? "Passed" : "Failed");

    // Test 2: List_first with one item in the list
    int item1 = 10; // Example item
    List_append(testList, &item1);
    item = List_first(testList);
    printf("Test 2 - Single item list: %s\n", (item == &item1 && List_curr(testList) == &item1) ? "Passed" : "Failed");

    // Test 3: List_first with multiple items in the list
    int item2 = 20; // Second item
    List_prepend(testList, &item2);
    item = List_first(testList);
    printf("Test 3 - Multiple items list: %s\n", (item == &item2 && List_curr(testList) == &item2) ? "Passed" : "Failed");

    printf("List_first tests completed.\n");
}

void testListLast() 
{
    printf("Testing List_last...\n");

    // Test 1: List_last on an empty list
    List* myList = List_create();
    void* item = List_last(myList);
    printf("Test 1 - Empty list: %s\n", (item == NULL && List_curr(myList) == NULL) ? "Passed" : "Failed");
    
    // Test 2: List_last with one item in the list
    int item1 = 10;
    List_append(myList, &item1);
    item = List_last(myList);
    printf("Test 2 - Single item list: %s\n", (item == &item1 && List_curr(myList) == &item1) ? "Passed" : "Failed");

    // Test 3: List_last with multiple items in the list
    int item2 = 20; // Second item
    List_append(myList, &item2);
    item = List_last(myList);
    printf("Test 3 - Multiple items list: %s\n", (item == &item2 && List_curr(myList) == &item2) ? "Passed" : "Failed");

    printf("List_last test completed.\n");
}

void testListNext() 
{
    printf("Testing List_next...\n");

    // Test 1: List_next on an empty list
    List* myList = List_create();
    void* item = List_next(myList);
    printf("Test 1 - Empty list: %s\n", (item == NULL) ? "Passed" : "Failed");
    
    // Test 2: List_next with 1 item in the list
    int item1 = 10;
    List_append(myList, &item1);
    item = List_next(myList);
    printf("Test 2 - Single item list: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 3: List_next with multiple items in the list
    int item2 = 20;
    List_append(myList, &item2);
    List_first(myList);
    item = List_next(myList);
    item = List_next(myList);
    printf("Test 3 - Multiple items lists: %s\n", (item == NULL) ? "Passed" : "Failed");

    printf("List_next test completed.\n");
}

void testListPrev() 
{
    printf("Testing List_prev...\n");

    // Test 1: List_prev on an empty list
    List* myList = List_create();
    void* item = List_prev(myList);
    printf("Test 1 - Empty list: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 2: Current item is beyond the end 
    int item1 = 10;
    List_append(myList, &item1);
    List_next(myList);
    item = List_prev(myList);
    printf("Test 2 - Current item is beyond the end: %s\n", (item == &item1) ? "Passed" : "Failed");

    // Test 3: Current item is before the start
    item = List_prev(myList);
    printf("Test 3 - Current item is before the start: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 4: Current item is at the start
    List_next(myList);
    item = List_prev(myList);
    printf("Test 4 - Current item is at the start: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 5: Current item is in the middle
    int item2 = 20, item3= 30;
    List_append(myList, &item2);
    List_append(myList, &item3);
    List_first(myList);
    List_next(myList);
    item = List_prev(myList);
    printf("Test 5 - Current item is at the middle: %s\n", (item == &item1) ? "Passed" : "Failed");

    printf("List_prev test completed.\n");
}

void testListCurr() 
{
    printf("Testing List_curr function.\n");

    // Test 1: List_curr on an empty list
    List* myList = List_create();
    void* item = List_curr(myList);
    printf("Test 1 - Empty list: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 2: Current item is beyond the end
    int item1 = 10;
    List_append(myList, &item1);
    List_next(myList);
    item = List_curr(myList);
    printf("Test 2 - Current item is beyond the end: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 3: Current item is before the start 
    List_first(myList);
    List_prev(myList);
    item = List_curr(myList);
    printf("Test 3 - Current item is before the start: %s\n", (item == NULL) ? "Passed" : "Failed");

    // Test 4: Normal case
    List_first(myList);
    item = List_curr(myList);
    printf("Test 4 - Normal case: %s\n", (item == &item1) ? "Passed" : "Failed");


    printf("List_curr test completed.\n");
}

void testListAppend() 
{
    printf("Testing List_append()...\n");

    // Test 1: List_append on an empty list
    List* myList = List_create();
    int item1 = 10;
    int result = List_append(myList, &item1);
    void* item = List_curr(myList);
    printf("Test 1 - Empty list: %s\n", (result == LIST_SUCCESS && item == &item1) ? "Passed" : "Failed");

    // Test 2: List_append multiple items
    int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("Append multiple items...");
    for (int i = 0; i < 9; i++) {
        int result = List_append(myList, &items[i]);
        printf("%s: Append item at location %d\n", (result == LIST_SUCCESS ? "Passed" : "Failed") ,(i + 1));
    }
    item = List_curr(myList);
    printf("Test 2 - Append multiple items: %s\n", (List_count(myList) == 10 && item == &items[8]) ? "Passed" : "Failed");

    // Test 3: List_append more than LIST_MAX_NUM_NODES
    int invalidItem = 999;
    result = List_append(myList, &invalidItem);
    printf("Test 3 - Append more than MAX_NODES: %s\n", (result == LIST_FAIL) ? "Passed" : "Failed");

    printf("List_append test completed.\n");
}

void testListPrepend() 
{
    printf("Testing List_prepend...\n");

    // Test 1: List_prepend on an empty list
    List* myList = List_create();
    int item1 = 10;
    int result = List_prepend(myList, &item1);
    void* item = List_curr(myList);
    printf("Test 1 - Empty list: %s\n", (result == LIST_SUCCESS && item == &item1) ? "Passed" : "Failed");

    // Test 2: List_prepend multiple items
    int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("Prepend multiple items...");
    for (int i = 0; i < 9; i++) {
        int result = List_prepend(myList, &items[i]);
        printf("%s: Prepend item at location %d\n", (result == LIST_SUCCESS ? "Passed" : "Failed") ,(i + 1));
    }
    item = List_curr(myList);
    printf("Test 2 - Prepend multiple items: %s\n", (List_count(myList) == 10 && item == &items[8]) ? "Passed" : "Failed");
    
    // Test 3: List_prepend more than LIST_MAX_NUM_NODES
    int invalidItem = 999;
    result = List_prepend(myList, &invalidItem);
    printf("Test 3 - Prepend more than MAX_NODES: %s\n", (result == LIST_FAIL) ? "Passed" : "Failed");

    printf("List_prepend test completed.\n");
}

void testListInsertAfter() 
{
    printf("Testing List_insert_after...\n");

    // Test 1: List_insert_after on an empty list
    List* myList = List_create();
    int item1 = 10;
    int result = List_insert_after(myList, &item1);
    void* item = List_curr(myList);
    printf("Test 1 - Empty list: %s\n", (result == LIST_SUCCESS && item == &item1) ? "Passed" : "Failed");

    // Test 2: Current pointer is before the start
    List_prev(myList);
    int item2 = 20;
    result = List_insert_after(myList, &item2);
    item = List_curr(myList);
    printf("Test 2 - Before the start: %s\n", (result == LIST_SUCCESS && item == &item2) ? "Passed" : "Failed");

    // Test 3: Current pointer is beyond the end
    List_last(myList);
    List_next(myList);
    int item3 = 30;
    result = List_insert_after(myList, &item3);
    item = List_curr(myList);
    printf("Test 3 - Beyond the end: %s\n", (result == LIST_SUCCESS && item == &item3) ? "Passed" : "Failed");

    // Test 4: Normal case
    List_prev(myList);
    int item4 = 40;
    result = List_insert_after(myList, &item4);
    item = List_curr(myList);
    printf("Test 4 - Normal case: %s\n", (result == LIST_SUCCESS && item == &item4) ? "Passed" : "Failed");
    
    // Test 5: Insert > MAX_NODES
    int items[] = {50, 60, 70, 80, 90, 100};
    for (int i = 0; i < 6; i++) {
        int result = List_insert_after(myList, &items[i]);
        printf("%s: Insert_after item at location %d\n", (result == LIST_SUCCESS ? "Passed" : "Failed") ,(i + 1));
    }
    int invalidItem = 999;
    result = List_insert_after(myList, &invalidItem);
    printf("Test 5 - Insert more than MAX_NODES: %s\n", (result == LIST_FAIL) ? "Passed" : "Failed");

    printf("List_insert_after test completed.\n");
}

void testListInsertBefore() 
{
    printf("Testing List_insert_before...\n");

    // Test 1; Insert_before on an empty list
    List* myList = List_create();
    int item1 = 10;
    int result = List_insert_before(myList, &item1);
    void* item = List_curr(myList);
    printf("Test 1 - Empty list: %s\n", (result == LIST_SUCCESS && item == &item1) ? "Passed" : "Failed");

    // Test 2: Current pointer is beofre the start
    List_prev(myList);
    int item2 = 20;
    result = List_insert_before(myList, &item2);
    item = List_curr(myList);
    printf("Test 2 - Before the start: %s\n", (result == LIST_SUCCESS && item == &item2) ? "Passed" : "Failed");

    // Test 3: Current pointer is beyond the end
    List_last(myList);
    List_next(myList);
    int item3 = 30;
    result = List_insert_before(myList, &item3);
    item = List_curr(myList);
    printf("Test 3 - Beyond the end: %s\n", (result == LIST_SUCCESS && item == &item3) ? "Passed" : "Failed");

    // Test 4: Normal case
    List_prev(myList);
    int item4 = 40;
    result = List_insert_before(myList, &item4);
    item = List_curr(myList);
    printf("Test 4 - Normal case: %s\n", (result == LIST_SUCCESS && item == &item4) ? "Passed" : "Failed");

    // Test 5: Insert > MAX_NODES
    int items[] = {50, 60, 70, 80, 90, 100};
    for (int i = 0; i < 6; i++) {
        int result = List_insert_before(myList, &items[i]);
        printf("%s: Insert_before item at location %d\n", (result == LIST_SUCCESS ? "Passed" : "Failed") ,(i + 1));
    }
    int invalidItem = 999;
    result = List_insert_before(myList, &invalidItem);
    printf("Test 5 - Insert more than MAX_NODES: %s\n", (result == LIST_FAIL) ? "Passed" : "Failed");

    printf("List_insert_before test completed.\n");
}

void testListRemove() 
{
    printf("Testing List_remove...\n");
    
    // Test 1: Removing from an empty list
    List* testList = List_create();
    void* removedItem = List_remove(testList);
    printf("Test 1 - Remove from empty list: %s\n", (removedItem == NULL) ? "Passed" : "Failed");

    // Test 2: Removing the only item
    int item1 = 10;
    List_append(testList, &item1);
    removedItem = List_remove(testList);
    printf("Test 2 - Remove only item: %s\n", (removedItem != NULL && List_count(testList) == 0 && *(int*)removedItem == item1) ? "Passed" : "Failed");

    // Add more items for further tests
    int items[] = {20, 30, 40, 50};
    for (int i = 0; i < 4; i++) {
        List_append(testList, &items[i]);
    }
    List_first(testList);

    // Test 3: Removing the first item
    removedItem = List_remove(testList);
    printf("Test 3 - Remove first item: %s\n", (removedItem != NULL && List_count(testList) == 3 && *(int*)removedItem == 20) ? "Passed" : "Failed");

    // Set current to last item
    List_last(testList);

    // Test 4: Removing the last item
    removedItem = List_remove(testList);
    printf("Test 4 - Remove last item: %s\n", (*(int*)removedItem == 50 && List_count(testList) == 2) ? "Passed" : "Failed");

    printf("List_remove tests completed.\n");

    // Test 5: If List_remove actually free node
    List* testList2 = List_create();
    int items2[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int flag = true;
    for (int i = 0; i < 8; i++) {
        int result = List_append(testList2, &items2[i]);
        printf("%s: Append item at location %d\n", (result == LIST_SUCCESS ? "Passed" : "Failed") ,(i + 1));
        if (result == LIST_FAIL) {
            flag = false;
            break;
        }
    }

    printf("Test 5 - Free node? %s\n", flag ? "Passed" : "Failed");
}

void testListTrim() 
{
    printf("Testing List_trim...\n");

    List* testList = List_create();
    
    // Test 1: Trimming an empty list
    void* item = List_trim(testList);
    printf("Test 1 - Trimming an empty list: %s\n", (List_trim(testList) == NULL) ? "Passed" : "Failed");

    // Test 2: Trimming a list with 1 item
    int item1 = 10;
    List_append(testList, &item1);
    item = List_trim(testList);
    printf("Test 2 - Trimming a list with 1 item: %s\n", (*(int*)item == item1 && List_count(testList) == 0) ? "Passed" : "Failed");

    // Test 3: Trimming a list with multiple items
    int items[] = {20, 30, 40, 50};
    for (int i = 0; i < 4; i++) {
        List_append(testList, &items[i]);
    }
    void* lastItemBeforeTrim = List_last(testList);
    item = List_trim(testList);
    printf("Test 3 - Trimming a list with multiple items: %s\n", (*(int*)item == *(int*)lastItemBeforeTrim && List_count(testList) == 3 ? "Passed" : "Failed"));

    printf("List_trim tests completed.\n");
}

void testListConcat()
{
    printf("Testing List_concat...\n");

    // Test 1: Concatenating 2 empty lists
    List* pList1 = List_create();
    List* pList2 = List_create();
    List_concat(pList1, pList2);
    printf("Test 1 - Concatenating two empty lists: %s\n", (List_count(pList1) == 0 && List_count(pList2) == 0) ? "Passed" : "Failed");

    // Test 2: Concatenating an empty list with a non-empty list
    int items[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        List_append(pList2, &items[i]);
    }
    List_concat(pList1, pList2);
    printf("Test 2 - Concatenating an empty list with a non-empty list: %s\n", (List_count(pList1) == 5 && List_count(pList2) == 0) ? "Passed" : "Failed");

    // Test 3: Concatenating a non-empty list with an empty list
    List* pList3 = List_create();
    List_concat(pList1, pList3);
    printf("Test 3 - Concatenating a non-empty list with an empty list: %s\n", (List_count(pList1) == 5 && List_count(pList2) == 0) ? "Passed" : "Failed");

    // Test 4: Concatenating 2 non-empty lists
    for (int i = 0; i < 5; i++) {
        List_append(pList2, &items[i]);
    }
    List_concat(pList1, pList2);
    printf("Test 4 - Concatenating two non-empty lists: %s\n", (List_count(pList1) == 10 && List_count(pList2) == 0) ? "Passed" : "Failed");

    printf("List_concat tests completed.\n");
}

void testListFree() 
{
    printf("Testing List_free...\n");

    List* myList = List_create();
    addItemsToList(myList, 5);

    List_free(myList, freeItem);

    printf("Test 1 - Normal case: %s\n", (List_curr(myList) == NULL) ? "Passed" : "Failed");

    printf("List_free tests completed\n");
}

void testListSearch() 
{
    printf("Testing List_search...\n");

    List* testList = List_create();
    int items[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        List_append(testList, &items[i]);
    }

    // Test 1: Search for an exsiting item
    int searchFor = 3;
    List_first(testList);
    void* foundItem = List_search(testList, intComparator, &searchFor);
    printf("Test 1 - Search for existing item: %s\n", (*(int*)foundItem == searchFor) ? "Passed" : "Failed");

    // Test 2: Search for non-existing item
    List_first(testList);
    int nonExist = 999;
    foundItem = List_search(testList, intComparator, &nonExist);
    printf("Test 2 - Search for non-existing item: %s\n", (foundItem == NULL) ? "Passed" : "Failed");

    // Test 3: Current pointer is before the start
    List_first(testList);
    List_prev(testList);
    foundItem = List_search(testList, intComparator, &searchFor);
    printf("Test 3 - Current pointer is before the start: %s\n", (*(int*)foundItem == searchFor) ? "Passed" : "Failed");
    
    printf("List_search tests completed\n");
}


bool intComparator(void* pItem, void* pComparisonArg) 
{
    int item = *(int*)pItem;
    int comparisonArg = *(int*)pComparisonArg;
    return item == comparisonArg;
}

void printList(List* pList) 
{
    assert(pList != NULL);

    if (pList->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* currentNode = List_first(pList);
    while (currentNode != NULL) {
        int* pItem = (int*) List_curr(pList);
        printf("%d ", *pItem);

        currentNode = List_next(pList);
    }

    printf("\n");
}

void freeItem(void* item) 
{
    free(item);
}

void addItemsToList(List* pList, int count) 
{
    for (int i = 0; i < count; i++) {
        int* newItem = (int*)malloc(sizeof(int));
        *newItem = i;
        List_append(pList, newItem);
    }
}