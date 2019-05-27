/*
 * stack.h
 * Structures
 *
 * Created by Mateus Nunes de B Magalhaes on 5/17/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/*
 *
 * Allocates a new stack item.
 *
 * @param error - A pointer to an integer that is used to pass along error codes.
 *
 * @return - On success, a pointer to the new stack item. Otherwise, NULL.
 *
 */

StackItem * newStackItem(int * error) {
    
    StackItem * item = (StackItem *) malloc(sizeof(StackItem));
    
    if (item == NULL) {
        
        *error = STACK_ERROR_MALLOC;
        
    } else {
        
        item->above = NULL;
        item->below = NULL;
        
        *error = STACK_ERROR_NONE;
        
    }
    
    return item;
    
}

/*
 *
 * Allocates a new stack and initializes it with the given parameters.
 *
 * @param policy - An integer that specifies the policy for removing items.
 * @param error - A pointer to an integer that is used to pass along error codes.
 *
 * @return - On success, a pointer to the new stack. Otherwise, NULL.
 *
 */

Stack * newStack(int policy, int * error) {
    
    Stack * stack = (Stack *) malloc(sizeof(Stack));
    
    if (stack == NULL) {
        
        *error = STACK_ERROR_MALLOC;
        
    } else {
        
        stack->count = 0;
        stack->policy = policy;
        
        stack->top = NULL;
        stack->bottom = NULL;
        
        *error = STACK_ERROR_NONE;
        
    }
    
    return stack;
    
}

/*
 *
 * Pushes a new item into the stack.
 *
 * @param stack - A pointer to a stack.
 * @param item - A pointer to a stack item.
 *
 */

void push(Stack * stack, StackItem * item) {
    
    if (stack != NULL && item != NULL) {
        
        if (stack->count == 0) {
            
            stack->top = item;
            stack->bottom = item;
            stack->count = 1;
            
        } else {
            
            item->below = stack->top;
            stack->top->above = item;
            stack->top = item;
            stack->count += 1;
            
        }
        
    }
    
}

/*
 *
 * Pops an item from the stack.
 *
 * @param stack - A pointer to a stack.
 *
 * @return - Pointer to a stack item or NULL if the stack was empty.
 *
 */

StackItem * pop(Stack * stack) {
    
    StackItem * item = NULL;
    
    if (stack != NULL && stack->count > 0) {
        
        if (stack->policy == STACK_POLICY_LIFO) {
            
            item = stack->top;
            stack->top = item->below;
            stack->count -= 1;
            item->below = NULL;
            
        } else {
            
            item = stack->bottom;
            stack->bottom = item->above;
            stack->count -= 1;
            item->above = NULL;
            
        }
        
        if (stack->count == 0) {
            
            stack->top = NULL;
            stack->bottom = NULL;
            
        }
        
    }
    
    return item;
    
}

/*
 *
 * Releses the stack and the stacked items.
 *
 * @param stack - A pointer to a stack.
 *
 */

void releaseStack(Stack * stack) {
    
    while (stack->count > 0) {
        
        free(pop(stack));
        
    }
    
    free(stack);
    
}
