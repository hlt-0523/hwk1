#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include <assert.h>


ListPtr createList( void (*dataPrinter)(void *data) ) {
	// Your implementation of createList()
    ListPtr newList = (ListPtr)malloc(sizeof(ListObj));
    if(newList == NULL) {
        return NULL;
    }
    newList->head = NULL;
    newList->dataPrinter = dataPrinter;
    newList->length = 0;
    return newList;
}

void destroyList(ListPtr *pL) {
	// Your implementation of destroyList()
    if(*pL == NULL) return;
    
    NodePtr current = (*pL)->head;
    NodePtr nextNode;
    
    while(current != NULL) {
        nextNode = current->next;
        freeNode(&current);
        current = nextNode;
    }

    free(*pL);
    *pL = NULL;
}


int lengthList(ListPtr L) {
	// Your implementation of lengthList()
    if(L == NULL) return -1;
    return L->length;
}

void printList(ListPtr L) {
	// Your implementation of printList()
    if(L == NULL) return;

    NodePtr current = L->head;
    while(current != NULL) {
        L->dataPrinter(current->data);
        current = current->next;
    }
}

void *getList(ListPtr L, int i) {
	// Your implementation of getList()
    // studied from https://stackoverflow.com/questions/20019979/list-in-c-using-void
    if(L == NULL || i >= L->length || i < 0) return NULL;

    NodePtr current = L->head;
    for(int j = 0; j < i && current != NULL; j++) {
        current = current->next;
    }
    return current->data;
}

void *deleteList(ListPtr L, int i) {
	// Your implementation of deleteList()
    if(L == NULL || i >= L->length || i < 0) return NULL;

    void *data;
    if(i == 0) {
        NodePtr temp = L->head;
        L->head = L->head->next;
        data = temp->data;
        freeNode(&temp);
    } else {
        NodePtr prev = L->head;
        for(int j = 0; j < i - 1; j++) {
            prev = prev->next;
        }
        
        NodePtr current = prev->next;
        
        prev->next = current->next;

        
        data = current->data;
        
        freeNode(&current);
    }
    L->length--;
    return data;
    
}

bool appendList(ListPtr L, void *data) {
	// Your implementation of appendList()
     if(L == NULL) 
        return false;

    NodePtr newNode = createNode(data);
    if(newNode == NULL) 
        return false;

    if(L->head == NULL) {
        L->head = newNode;
    } else {
        NodePtr current = L->head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    L->length++;


    return true;
}


NodePtr createNode(void *data) {
    NodePtr newNode = (NodePtr)malloc(sizeof(NodeObj));
    if(newNode == NULL) {
        return NULL;
    }


    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeNode(NodePtr *node) {
    if(*node != NULL) {

        free(*node);
        *node = NULL;
    
    }
}
