/*
 * structure-stack.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 3/14/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(int argc, const char * argv[]) {
    
    int i;
    int error = STACK_ERROR_NONE;
    char str[] = "...ssenkrad olleH\0";
    
    Stack * stack = newStack(STACK_POLICY_LIFO, &error);
    
    printf("Stacking: ");
    
    for (i = 0; str[i] != '\0'; i++) {
        
        StackItem * item = newStackItem(&error);
        
        item->cchar = str[i];
        
        push(stack, item);
        
        printf("%c", str[i]);
        
    }
    
    printf("\nPopping: ");
    
    for (; i > 0; i--) {
        
        StackItem * item = pop(stack);
        
        printf("%c", item->cchar);
        
    }
    
    printf("\n");
    
    return 0;
    
}
