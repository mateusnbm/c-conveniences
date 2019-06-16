/*
 * list.c
 * Structures
 *
 * Created by Mateus Nunes de B Magalhaes on 3/14/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
 *
 * Allocates a new list node and initializes it with the given parameters.
 *
 * @param nodeID - An integer that identifies the node.
 * @param sorter - An integer that can be used to sort nodes.
 * @param data - A void pointer that can be used to reference related data structures.
 * @param error - A pointer to an integer that is used to pass along error codes.
 *
 * @return - On success, a pointer to the new node. Otherwise, NULL.
 *
 */

ListNode * newListNode(int nodeID, int sorter, void * data, int * error) {
    
    ListNode * node = (ListNode *) malloc(sizeof(ListNode));
    
    if (node == NULL) {
        
        *error = LIST_ERROR_MALLOC;
        
    } else {
        
        node->nodeID = nodeID;
        node->sorter = sorter;
        node->data = data;
        
        node->previous = NULL;
        node->next = NULL;
        
        *error = LIST_ERROR_NONE;
        
    }
    
    return node;
    
}

/*
 *
 * Finds the first node of a list with the given ID.
 *
 * @param head - The list's head.
 * @param nodeID - The node's ID.
 *
 * @return A pointer to the node, if, it was found. Otherwise, NULL.
 *
 */

ListNode * getNode(ListNode * head, int nodeID) {
    
    while (head != NULL && head->nodeID != nodeID) {
        
        head = head->next;
        
    }
    
    return head;
    
}

/*
 *
 * Appends a new node to the given list.
 *
 * @param head - The list's head.
 * @param node - The node to append.
 * @param order - Determines if the insertion should organize the nodes in ascending, descending or no order at all.
 *
 * @return - The list's starting node (it's head).
 *
 */

ListNode * appendNode(ListNode * head, ListNode * node, int order) {
    
    if (head == NULL) {
        
        head = node;
        
    } else if (node->sorter <= head->sorter && order == LIST_APPEND_ASCENDING) {
        
        node->next = head;
        head->previous = node;
        
        head = node;
        
    } else if (node->sorter >= head->sorter && order == LIST_APPEND_DESCENDING) {
        
        node->next = head;
        head->previous = node;
        
        head = node;
        
    } else {
        
        ListNode * aux = head;
        
        if (order == LIST_APPEND_UNORDERED) {
            
            while (aux->next != NULL) { aux = aux->next; }
            
        } else if (order == LIST_APPEND_ASCENDING) {
            
            while (aux->next != NULL && node->sorter >= aux->next->sorter) { aux = aux->next; }
            
        } else if (order == LIST_APPEND_DESCENDING) {
            
            while (aux->next != NULL && node->sorter <= aux->next->sorter) { aux = aux->next; }
            
        }
        
        if (aux->next != NULL) {
            
            aux->next->previous = node;
            node->next = aux->next;
            
        }
        
        aux->next = node;
        node->previous = aux;
        
    }
    
    return head;
    
}

/*
 *
 * Finds and removes the first node that matches the given ID.
 *
 * @param head - The list's head.
 * @param nodeID - The node's ID.
 *
 * @return - The list's starting node (it's head).
 *
 */

ListNode * removeNode(ListNode * head, int nodeID) {
    
    if (head != NULL) {
        
        if (head->nodeID == nodeID) {
            
            head = head->next;
            head->previous = NULL;
            
        }else{
            
            ListNode * aux = head;
            
            while (aux->next != NULL && aux->next->nodeID != nodeID) {
                
                aux = aux->next;
                
            }
            
            ListNode * foundNode = aux->next;
            
            if (foundNode != NULL) {
                
                aux->next = foundNode->next;
                aux->next->previous = aux;
                
                foundNode->next = NULL;
                foundNode->previous = NULL;
                
            }
            
        }
        
    }
    
    return head;
}

/*
 *
 * Frees the dynamically allocated memory used to manage the list.
 *
 * @param head - The list's head.
 *
 */

void releaseList(ListNode * head) {
    
    if (head->next != NULL) {
        
        releaseList(head->next);
        
    }
    
    free(head);
    
}

/*
 *
 * Prints the ID of every node on a list.
 *
 * @param head - The list's head.
 *
 */

void printListNodes(ListNode * head) {
    
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
