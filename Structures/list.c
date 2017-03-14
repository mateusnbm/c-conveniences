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
 * Allocates a new list node and initialized it with the given id and data.
 *
 * @param id - Node's id.
 * @param data - Node's void pointer.
 *
 * @return - A pointer to the new node.
 *
 */

ListNode *newListNode(int id, void *data) {
    
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    
    node->id = id;
    node->data = data;
    
    node->previous = NULL;
    node->next = NULL;
    
    return node;
}

/*
 *
 * <#Description#>
 *
 * @param head <#head description#>
 *
 */

void printNodes(ListNode *head) {
    
    if (head == NULL) {
        
        printf("No nodes.");
        
    }else{
        
        printf("Nodes: ");
        
        while (head != NULL) {
            
            if (head->next == NULL) {
                
                printf("%i", head->id);
                
            }else{
                
                printf("%i, ", head->id);
                
            }
            
            head = head->next;
            
        }
        
        printf(".\n");
        
    }
    
}

/*
 *
 * <#Description#>
 *
 * @param head - <#head description#>
 * @param node - <#node description#>
 *
 * @return - <#return value description#>
 *
 */

ListNode *appendNode(ListNode *head, ListNode *node) {
    
    if (head == NULL) {
        
        head = node;
        
    }else{
        
        ListNode *item = head;
        
        while (item->next != NULL) {
            
            item = item->next;
            
        }
        
        item->next = node;
        
    }
    
    return head;
}

void demoList() {
    
    int i;
    
    ListNode *head;
    
    // Populate with nodes 10, 20, 30, 40, 50, 60, 70, 80, 90, 100.
    
    for (i = 0; i < 10; i++) {
        
        int id = (i + 1) * 10;
        
        ListNode *node = newListNode(id, NULL);
        
        head = appendNode(head, node);
        
    }
    
    // Print nodes.
    
    printNodes(head);
    
}
