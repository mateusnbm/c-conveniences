/*
 * structure-list.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 3/14/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, const char * argv[]) {
    
    int i;
    int k;
    int error;
    
    ListNode *node;
    ListNode *head;
    
    srand((unsigned int)time(NULL));
    
    // Create a list.
    
    head = newListNode(10, 10, NULL, &error);
    
    if (error != LIST_ERROR_NONE) { }
    
    printf("Created a list.\n");
    
    printListNodes(head);
    
    // Insert ten nodes with a random nodeID and sorter.
    
    for (i = 0; i < 10; i++) {
        
        k = (rand() % 1000) + 1;
        
        node = newListNode(k, k, NULL, &error);
        
        if (error == LIST_ERROR_NONE) {
            
            head = appendNode(head, node, LIST_APPEND_UNORDERED);
            
        }
        
    }
    
    printf("Inserted ten random nodes.\n");
    
    printListNodes(head);
    
    // Insert a node respecting the sorters order.
    
    k = (rand() % 1000) + 1;
    
    node = newListNode(k, k, NULL, &error);
    
    if (error == LIST_ERROR_NONE) {
        
        head = appendNode(head, node, LIST_APPEND_DESCENDING);
        
    }
    
    printf("Inserted a node (sorter = %i) respecting the list order.\n", k);
    
    printListNodes(head);
    
    // Free dynamically allocated memory.
    
    releaseList(head);
    
    return 0;
    
}
