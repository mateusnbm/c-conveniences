/*
 * stack.h
 * Structures
 *
 * Created by Mateus Nunes de B Magalhaes on 5/17/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#ifndef stack_h
#define stack_h

#define STACK_ERROR_NONE 0
#define STACK_ERROR_MALLOC 1

#define STACK_POLICY_LIFO 0
#define STACK_POLICY_FIFO 1

/*
 *
 * A data structure that represents a node of a list. It has the following variables:
 *
 * @var nodeID - An integer that identifies the node.
 * @var sorter - An integer that can be used to sort nodes.
 * @var data - A void pointer that can be used to reference related data structures.
 * @var previous - The list node that comes before the present node.
 * @var next - The list node that follows the present node.
 *
 */

typedef struct stackItem {
    
    char cchar;
    
    struct stackItem * above;
    struct stackItem * below;
    
} StackItem;

/*
 *
 * A data structure that represents a node of a list. It has the following variables:
 *
 * @var nodeID - An integer that identifies the node.
 * @var sorter - An integer that can be used to sort nodes.
 * @var previous - The list node that comes before the present node.
 * @var next - The list node that follows the present node.
 *
 */

typedef struct stack {
    
    int count;
    int policy;
    
    struct stackItem * top;
    struct stackItem * bottom;
    
} Stack;

/*
 *
 * Allocates a new stack item.
 *
 * @param error - A pointer to an integer that is used to pass along error codes.
 *
 * @return - On success, a pointer to the new stack item. Otherwise, NULL.
 *
 */

StackItem * newStackItem(int * error);

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

Stack * newStack(int policy, int * error);

/*
 *
 * Pushes a new item into the stack.
 *
 * @param stack - A pointer to a stack.
 * @param item - A pointer to a stack item.
 *
 */

void push(Stack * stack, StackItem * item);

/*
 *
 * Pops an item from the stack.
 *
 * @param stack - A pointer to a stack.
 *
 * @return - Pointer to a stack item or NULL if the stack was empty.
 *
 */

StackItem * pop(Stack * stack);

/*
 *
 * Releses the stack and the stacked items.
 *
 * @param stack - A pointer to a stack.
 *
 */

void releaseStack(Stack * stack);

#endif /* stack_h */
