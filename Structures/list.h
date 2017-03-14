//
//  list.h
//  Structures
//
//  Created by Mateus Nunes de B Magalhaes on 3/14/17.
//  Copyright © 2017 mateusnbm. All rights reserved.
//

#ifndef list_h
#define list_h

typedef struct listNode {
    
    int id;
    
    void *data;
    
    struct listNode *previous;
    struct listNode *next;
    
} ListNode;

void demoList();

#endif /* list_h */
