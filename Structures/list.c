//
//  list.c
//  Structures
//
//  Created by Mateus Nunes de B Magalhaes on 3/14/17.
//  Copyright © 2017 mateusnbm. All rights reserved.
//

#include "list.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *
 * Allocate a new ListNode and initializes it with the given sorter and data pointer.
 *
 * @param nodeID - An integer to identify the node.
 * @param sorter - An integer used to sort nodes.
 * @param data - Node's data pointer.
 * @param error - A pointer to an integer, used to return error codes.
 *
 * @return - On success, a pointer to the new node. On error, NULL.
 *
 */

ListNode *newListNode(int nodeID, int sorter, void *data, int *error) {
    
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    
    if (node == NULL) {
        
        *error = LIST_MALLOC_ERROR;
        
    }else{
        
        node->nodeID = nodeID;
        node->sorter = sorter;
        node->data = data;
        
        node->previous = NULL;
        node->next = NULL;
        
        *error = LIST_NO_ERROR;
        
    }
    
    return node;
}

/*
 * Find the first node with the given nodeID on the list.
 *
 * @param list - The list to be searched.
 * @param nodeID - The nodeID of the node to be found.
 *
 * @return If found, a pointer to the node. Else, NULL;
 *
 */

ListNode *getNode(ListNode *list, int nodeID) {
    
    while (list != NULL && list->nodeID != nodeID) {
        
        list = list->next;
        
    }
    
    return list;
}

/*
 *
 * Append a node to the end of the list.
 *
 * @param head - The list starting node.
 * @param node - The node to append.
 *
 * @return - The list starting node.
 *
 */

ListNode *appendNode(ListNode *list, ListNode *node) {
    
    if (list == NULL) {
        
        list = node;
        
    }else{
        
        ListNode *aux = list;
        
        while (aux->next != NULL) {
            
            aux = aux->next;
            
        }
        
        aux->next = node;
        node->previous = aux;
        
    }
    
    return list;
}

/*
 *
 * Append a node to a list, inserting it after the node with the closest lower id.
 *
 * @param head - The list starting node.
 * @param node - The node to append.
 *
 * @return - The list starting node.
 *
 */

ListNode *appendNodeOrdered(ListNode *list, ListNode *node) {
    
    if (list == NULL) {
        
        list = node;
        
    }else if (list->sorter >= node->sorter) {
        
        node->next = list;
        list->previous = node;
        
        list = node;
        
    }else{
        
        ListNode *aux = list;
        
        while (aux->next != NULL && aux->next->sorter <= node->sorter) {
            
            aux = aux->next;
            
        }
        
        aux->next->previous = node;
        node->previous = aux;
        
        node->next = aux->next;
        aux->next = node;
        
    }
    
    return list;
}

/*
 *
 * Find and remove the first node identified by the given nodeID found on the list.
 *
 * @param list - The list to be searched and updated.
 * @param nodeID - The nodeID of the node to be removed.
 *
 * @return - The list starting node.
 *
 */

ListNode *removeNode(ListNode *list, int nodeID) {
    
    if (list != NULL) {
        
        if (list->nodeID == nodeID) {
            
            list = list->next;
            list->previous = NULL;
            
        }else{
            
            ListNode *aux = list;
            
            while (aux->next != NULL && aux->next->nodeID != nodeID) {
                
                aux = aux->next;
                
            }
            
            ListNode *foundNode = aux->next;
            
            if (foundNode != NULL) {
                
                aux->next = foundNode->next;
                aux->next->previous = aux;
                
                foundNode->next = NULL;
                foundNode->previous = NULL;
                
            }
            
        }
        
    }
    
    return list;
}

/*
 *
 * Sort a list of nodes, according to the sorter parameter, using the
 *
 * @param list - The list to be sorted.
 *
 * @return - The list starting node.
 *
 */

ListNode *sortList(ListNode *list) {
    
    //
    
    return list;
}

/*
 * Free the memory pointers in a list.
 *
 * @param list - The list whose pointer should be freed.
 *
 */

void releaseList(ListNode *list) {
    
    if (list->next != NULL) {
        
        releaseList(list->next);
        
    }
    
    free(list);
    
}

/*
 *
 * Print all nodes id's from a given head.
 *
 * @param head - The first node to print and start iterating.
 *
 */

void printNodes(ListNode *head) {
    
    if (head == NULL) {
        
        printf("No nodes.");
        
    }else{
        
        printf("Nodes: ");
        
        while (head != NULL) {
            
            if (head->next == NULL) {
                
                printf("%i", head->sorter);
                
            }else{
                
                printf("%i, ", head->sorter);
                
            }
            
            head = head->next;
            
        }
        
        printf(".\n");
        
    }
    
}

/*
 *
 * Demonstrates the capabilities available.
 *
 */

int demoList() {
    
    int i;
    int k;
    int error;
    
    ListNode *node;
    ListNode *head;
    
    srand((unsigned int)time(NULL));
    
    // Create a list.
    
    head = newListNode(10, 10, NULL, &error);
    
    if (error != LIST_NO_ERROR) {
        
        return error;
        
    }
    
    printf("Created a list.\n");
    
    printNodes(head);
    
    // Insert ten nodes with a random nodeID and sorter.
    
    for (i = 0; i < 10; i++) {
        
        k = (rand() % 1000) + 1;
        
        node = newListNode(k, k, NULL, &error);
        
        if (error == LIST_NO_ERROR) {
            
            head = appendNode(head, node);
            
        }
        
    }
    
    printf("Inserted ten random nodes.\n");
    
    printNodes(head);
    
    // Insert a node respecting the sorters order.
    
    k = (rand() % 1000) + 1;
    
    node = newListNode(k, k, NULL, &error);
    
    if (error == LIST_NO_ERROR) {
        
        head = appendNodeOrdered(head, node);
        
    }
    
    printf("Inserted a node (sorter = %i) respecting the list order.\n", k);
    
    printNodes(head);
    
    // Sort nodes and print them.
    
    head = sortList(head);
    
    printf("Sorted the list.\n");
    
    printNodes(head);
    
    // Free dynamically allocated memory.
    
    releaseList(head);
    
    return error;
    
}
