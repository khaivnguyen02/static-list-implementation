#include <stdio.h>
#include <assert.h>
#include "list.h"

static Node nodes[LIST_MAX_NUM_NODES];
static List lists[LIST_MAX_NUM_HEADS];
static Node* freeNodeHead = NULL;
static List* freeListHead = NULL;
static bool isInitialized = false;

static void initialize()
{
    for (int i = 0; i < LIST_MAX_NUM_NODES - 1; i++) {
        nodes[i].nextFree = &nodes[i + 1];
    }
    nodes[LIST_MAX_NUM_NODES - 1].nextFree = NULL;
    freeNodeHead = &nodes[0];

    for (int i = 0; i < LIST_MAX_NUM_HEADS - 1; i++) {
        lists[i].nextFree = &lists[i + 1];
    }
    lists[LIST_MAX_NUM_HEADS - 1].nextFree = NULL;
    freeListHead = &lists[0];

    isInitialized = true;
}

List* List_create()
{
    if (!isInitialized) {
        initialize();
    }

    if (freeListHead == NULL) {
        return NULL; // No free list head available
    }

    // Allocate a new list from the free list head
    List* newList = freeListHead;
    freeListHead = newList->nextFree;

    // Initialize the new list
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    newList->count = 0;
    newList->nextFree = NULL;
    newList->state = LIST_OOB_START;

    return newList;
}

int List_count(List* pList) 
{
    assert(pList != NULL);

    return pList->count;
}

void* List_first(List* pList) 
{
    assert(pList != NULL);

    if (pList->head == NULL) {
        pList->current = NULL;
        return NULL;
    }

    pList->current = pList->head;

    return pList->head->item;
}

void* List_last(List* pList)
{
    assert(pList != NULL);

    if (pList->head == NULL) {
        pList->current = NULL;
        return NULL;
    }

    pList->current = pList->tail;

    return pList->tail->item;
}

void* List_next(List* pList)
{
    assert(pList != NULL);

    // Empty list
    if (pList->head == NULL) {
        pList->state = LIST_OOB_END;
        return NULL;
    }

    // Current item is beyond the end of the list
    if (pList->current == NULL && pList->state == LIST_OOB_END) {
        return NULL;
    }

    // Current item is before the start of the list
    if (pList->current == NULL && pList->state == LIST_OOB_START) {
        pList->current = pList->head;
        pList->state = 0;
        return pList->current->item;
    }

    // Current item is at the end
    if (pList->current == pList->tail) {
        pList->state = LIST_OOB_END;
        pList->current = NULL;
        return NULL;
    }

    // Advance the current item
    pList->current = pList->current->next;

    // Return the item of the new current node
    return pList->current->item;
}

void* List_prev(List* pList)
{
    assert(pList != NULL);

    // Empty list
    if (pList->head == NULL) {
        return NULL;
    }

    // Current item is beyond the end of the list
    if (pList->current == NULL && pList->state == LIST_OOB_END) {
        pList->current = pList->tail;
        return pList->tail->item;
    }

    // Current item is before the start
    if (pList->current == NULL && pList->state == LIST_OOB_START) {
        return NULL;
    }

    // Current item is at the start
    if (pList->current == pList->head) {
        pList->state = LIST_OOB_START;
        pList->current = NULL;
        return NULL;
    }

    // Backs up the current item
    pList->current = pList->current->prev;
    
    // Return the item of the new current node
    return pList->current->item;
}

void* List_curr(List* pList)
{
    assert(pList != NULL);

    if (pList->head == NULL || pList->current == NULL) {
        return NULL;
    }
    
    return pList->current->item;
}

static Node* allocateNode() {
    if (freeNodeHead == NULL) {
        // No free nodes available
        return NULL;
    }

    // Take the first free node
    Node* newNode = freeNodeHead;
    freeNodeHead = newNode->nextFree;

    // Reset the new node's values
    newNode->item = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->nextFree = NULL;

    return newNode;
}

int List_insert_after(List* pList, void* pItem)
{
    assert(pList != NULL);

    if (pList->count == 0 || pList->head == NULL || pList->tail == NULL) {
        // List is empty, append the item
        return List_append(pList, pItem);
    }

    if (pList->current == NULL && pList->state == LIST_OOB_START) {
        // Current pointer is before the start of the list
        return List_prepend(pList, pItem);
    }

    if (pList->current == NULL && pList->state == LIST_OOB_END) {
        // Current pointer is beyond the end of the list
        return List_append(pList, pItem);
    }

    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return LIST_FAIL; // No available nodes
    }

    newNode->item = pItem;

    newNode->next = pList->current->next;
    newNode->prev = pList->current;
    if (pList->current->next != NULL) {
        pList->current->next->prev = newNode;
    }
    pList->current->next = newNode;

    if (pList->tail == pList->current) {
        pList->tail = newNode;
    }

    pList->current = newNode;
    pList->count++;

    return LIST_SUCCESS;
}

int List_insert_before(List* pList, void* pItem)
{
    assert(pList != NULL);

    if (pList->count == 0 || pList->head == NULL || pList->tail == NULL) {
        // List is empty, prepend the item
        return List_prepend(pList, pItem);
    }

    if (pList->current == NULL && pList->state == LIST_OOB_START) {
        // Current pointer is before the start of the list
        return List_prepend(pList, pItem);
    }

    if (pList->current == NULL && pList->state == LIST_OOB_END) {
        // Current pointer is beyond the end of the list
        return List_append(pList, pItem);
    }

    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return LIST_FAIL;
    }

    newNode->item = pItem;

    newNode->prev = pList->current->prev;
    newNode->next = pList->current;
    if (pList->current->prev != NULL) {
        pList->current->prev->next = newNode;
    }
    pList->current->prev = newNode;

    if (pList->head == pList->current) {
        pList->head = newNode;
    }

    pList->current = newNode;
    pList->count++;

    return LIST_SUCCESS;
}

int List_append(List* pList, void* pItem)
{
    assert(pList != NULL);
    
    // Allocate a new node
    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return LIST_FAIL;
    }

    // Initialize the new node with the given item
    newNode->item = pItem;
    newNode->next = NULL; 

    // Insert the new node
    if (pList->head == NULL) {
        // The list is currently empty
        pList->head = newNode;
        pList->tail = newNode;
        newNode->prev = NULL;
    } else {
        newNode->prev = pList->tail;
        pList->tail->next = newNode;
        pList->tail = newNode;
    }

    pList->current = newNode;
    pList->count++;

    return LIST_SUCCESS;
}

int List_prepend(List* pList, void* pItem)
{
    assert(pList != NULL);

    // Allocate a new node
    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return LIST_FAIL;
    }

    // Initialize the new node with the given item
    newNode->item = pItem;
    newNode->prev = NULL;

    if (pList->count == 0 || pList->head == NULL || pList->tail == NULL) {
        // The list is currently empty
        pList->head = newNode;
        pList->tail = newNode;
        newNode->next = NULL;
    } else {
        newNode->next = pList->head;
        pList->head->prev = newNode;
        pList->head = newNode;
    }

    pList->current = newNode;
    pList->count++;

    return LIST_SUCCESS;
}

static void freeNode(Node* pNode) {
    pNode->item = NULL;
    pNode->next = NULL;
    pNode->prev = NULL;

    pNode->nextFree = freeNodeHead;
    freeNodeHead = pNode;
}

void* List_remove(List* pList)
{
    assert(pList != NULL);

    if (pList->head == NULL || pList->current == NULL) {
        return NULL;
    }

    void* item = pList->current->item;

    if (pList->count == 1) {
        pList->head = NULL;
        pList->tail = NULL;
        pList->state = LIST_OOB_END;
    } else if (pList->current == pList->head) {
        pList->head = pList->current->next;
        pList->head->prev = NULL;
    } else if (pList->current == pList->tail) {
        pList->tail = pList->current->prev;
        pList->tail->next = NULL;
        pList->state = LIST_OOB_END;
    } else {
        pList->current->prev->next = pList->current->next;
        pList->current->next->prev = pList->current->prev;
    }

    Node* temp = pList->current;
    pList->current = pList->current->next;

    freeNode(temp);
    
    pList->count--;

    return item;
}

void* List_trim(List* pList) 
{
    assert(pList != NULL);

    if (pList->head == NULL) {
        return NULL;
    }

    void* item = pList->tail->item;

    if (pList->count == 1) {
        freeNode(pList->tail);

        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
    } else {
        Node* newTail = pList->tail->prev;
        newTail->next = NULL;

        freeNode(pList->tail);

        pList->tail = newTail;
        pList->current = newTail;
    }

    pList->count--;

    return item;
}

static void freeList(List* pList)
{
    assert(pList != NULL);

    pList->head = NULL;
    pList->tail = NULL;
    pList->current = NULL;
    pList->count = 0;
    pList->state = LIST_OOB_START;

    pList->nextFree = freeListHead;
    freeListHead = pList;
}

void List_concat(List* pList1, List* pList2)
{
    assert(pList1 != NULL);
    assert(pList2 != NULL);
    assert(pList1 != pList2);

    if (pList1->head == NULL) {
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
        pList1->state = LIST_OOB_START;
    } else if (pList2->head != NULL) {
        pList1->tail->next = pList2->head;
        pList2->head->prev = pList1->tail;
        pList1->tail = pList2->tail;
    }

    pList1->count += pList2->count;

    freeList(pList2);
}

void List_free(List* pList, FREE_FN pItemFreeFn) 
{
    assert(pList != NULL);
    assert(pItemFreeFn != NULL);

    Node* node = pList->head;
    while (node != NULL) {
        if (node->item != NULL) {
            (*pItemFreeFn)(node->item);
        }

        Node* temp = node;
        node = node->next;
        freeNode(temp);
    }

    freeList(pList);
}

void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg)
{
    assert(pList != NULL);
    assert(pComparator != NULL);

    if (pList->head == NULL) {
        // Empty list
        pList->state = LIST_OOB_END;
        return NULL;
    }

    if (pList->current == NULL && pList->state == LIST_OOB_END) {
        // Current pointer is beyond the end
        return NULL;
    }

    // Check if the current pointer is before the start of the list
    Node* startNode = (pList->current == NULL && pList->state == LIST_OOB_START) ? pList->head : pList->current;

    for (Node* node = startNode; node != NULL; node = node->next) {
        if (pComparator(node->item, pComparisonArg)) {
            // Match found, update current and return item
            pList->current = node;
            return node->item;
        }
    }

    // No match is found, the current pointer is left beyond the end of the list
    pList->current = NULL;
    pList->state = LIST_OOB_END;

    return NULL;
}