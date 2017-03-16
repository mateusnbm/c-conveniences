//
//  list.c
//  Structures
//
//  Created by Mateus Nunes de B Magalhaes on 3/14/17.
//  Copyright © 2017 mateusnbm. All rights reserved.
//

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

/*
 *
 * Allocate a new ListNode and initializes it with the given sorter and data pointer.
 *
 * @param sorter - An integer used to sort nodes.
 * @param data - Node's data pointer.
 * @param error - A pointer to an integer, used to return error codes.
 *
 * @return - On success, a pointer to the new node. On error, NULL.
 *
 */

ListNode *newListNode(int sorter, void *data, int *error) {
    
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    
    if (node == NULL) {
        
        *error = LIST_MALLOC_ERROR;
        
    }else{
        
        node->sorter = sorter;
        node->data = data;
        
        node->previous = NULL;
        node->next = NULL;
        
        *error = LIST_NO_ERROR;
        
    }
    
    return node;
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
 * <#Description#>
 *
 * @param list <#list description#>
 *
 * @return <#return value description#>
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
    int error;
    
    ListNode *node;
    ListNode *head;
    
    // Create a list.
    
    head = newListNode(10, NULL, &error);
    
    if (error != LIST_NO_ERROR) {
        
        return error;
        
    }
    
    // Insert nodes 20, 30, 40, 50, 60, 70, 80, 90, 100.
    
    for (i = 1; i < 10; i++) {
        
        int id = (i + 1) * 10;
        
        node = newListNode(id, NULL, &error);
        
        if (error == LIST_NO_ERROR) {
            
            head = appendNode(head, node);
            
        }
        
    }
    
    // Insert node 55, ordered.
    
    node = newListNode(55, NULL, &error);
    
    if (error == LIST_NO_ERROR) {
        
        head = appendNodeOrdered(head, node);
        
    }
    
    // Insert node 34 at the end of the list.
    
    node = newListNode(34, NULL, &error);
    
    if (error == LIST_NO_ERROR) {
        
        head = appendNode(head, node);
        
    }
    
    // Insert node 2, ordered.
    
    node = newListNode(2, NULL, &error);
    
    if (error == LIST_NO_ERROR) {
        
        head = appendNodeOrdered(head, node);
        
    }
    
    // Print nodes.
    
    printNodes(head);
    
    // Sort nodes and print them.
    
    //
    
    // Free the pointers.
    
    releaseList(head);
    
    return error;
    
}
