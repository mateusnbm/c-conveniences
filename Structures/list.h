/*
 * list.h
 * Structures
 *
 * Created by Mateus Nunes de B Magalhaes on 3/14/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#ifndef list_h
#define list_h

#define LIST_ERROR_NONE 0
#define LIST_ERROR_MALLOC 100

#define LIST_APPEND_UNORDERED 0
#define LIST_APPEND_ASCENDING 1
#define LIST_APPEND_DESCENDING 2

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

typedef struct listNode {
    
    int nodeID;
    int sorter;
    void * data;
    
    struct listNode * previous;
    struct listNode * next;
    
} ListNode;

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

ListNode * newListNode(int nodeID, int sorter, void * data, int * error);

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

ListNode * getNode(ListNode * head, int nodeID);

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

ListNode * appendNode(ListNode * head, ListNode * node, int order);

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

ListNode * removeNode(ListNode * head, int nodeID);

/*
 *
 * Frees the dynamically allocated memory used to manage the list.
 *
 * @param head - The list's head.
 *
 */

void releaseList(ListNode * head);

/*
 *
 * Prints the ID of every node on the list.
 *
 * @param head - The list's head.
 *
 */

void printListNodes(ListNode * head);

#endif /* list_h */
