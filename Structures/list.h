//
//  list.h
//  Structures
//
//  Created by Mateus Nunes de B Magalhaes on 3/14/17.
//  Copyright © 2017 mateusnbm. All rights reserved.
//

#ifndef list_h
#define list_h

#define LIST_NO_ERROR 0
#define LIST_MALLOC_ERROR 100

typedef struct listNode {
    
    int sorter;
    void *data;
    
    struct listNode *previous;
    struct listNode *next;
    
} ListNode;

int demoList();

#endif /* list_h */
