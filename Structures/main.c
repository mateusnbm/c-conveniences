//
//  main.c
//  Structures
//
//  Created by Mateus Nunes de B Magalhaes on 3/14/17.
//  Copyright © 2017 mateusnbm. All rights reserved.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "quicksort.h"
#include "bubblesort.h"
#include "mergesort.h"

void demoList(void);
void demoQuicksort(void);
void demoBubblesort(void);
void demoMergesort(void);

int main(int argc, const char * argv[]) {
    
    //demoList();
    //demoQuicksort();
    //demoBubblesort();
    demoMergesort();
    
    return 0;
}

void demoList() {
    
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
    
}

void demoQuicksort() {
    
    int i;
    int numbersCount = 1000;
    
    int *arr = (int *) malloc(numbersCount * sizeof(int));
    
    srand((int)time(NULL));
    
    /*  Populate the array with random numbers. */
    
    for (i = 0; i < numbersCount; i++) {
        
        arr[i] = (rand() % numbersCount) + 1;
        
    }
    
    /* Print the unsorted array. */
    
    printf("Unsorted array:\n");
    
    quicksortPrintIntegers(arr, numbersCount);
    
    /* Sort the array using quicksort. */
    
    quicksort(arr, 0, numbersCount-1);
    
    /* Print the sorted array. */
    
    printf("Sorted array:\n");
    
    quicksortPrintIntegers(arr, numbersCount);
    
    /* Free the memory dynamically allocated. */
    
    free(arr);
    
}

void demoBubblesort() {
    
    int i;
    int numbersCount = 10;
    
    int *arr = (int *) malloc(numbersCount * sizeof(int));
    
    srand((int)time(NULL));
    
    /*  Populate the array with random numbers. */
    
    for (i = 0; i < numbersCount; i++) {
        
        arr[i] = (rand() % numbersCount) + 1;
        
    }
    
    /* Print the unsorted array. */
    
    printf("Unsorted array:\n");
    
    quicksortPrintIntegers(arr, numbersCount);
    
    /* Sort the array using quicksort. */
    
    bubblesort(arr, numbersCount);
    
    /* Print the sorted array. */
    
    printf("Sorted array:\n");
    
    quicksortPrintIntegers(arr, numbersCount);
    
    /* Free the memory dynamically allocated. */
    
    free(arr);
    
}

void demoMergesort() {
    
    int i;
    int numbersCount = 10;
    
    int *arr = (int *) malloc(numbersCount * sizeof(int));
    
    srand((int)time(NULL));
    
    /*  Populate the array with random numbers. */
    
    for (i = 0; i < numbersCount; i++) {
        
        arr[i] = (rand() % numbersCount) + 1;
        
    }
    
    /* Print the unsorted array. */
    
    printf("Unsorted array:\n");
    
    quicksortPrintIntegers(arr, numbersCount);
    
    /* Sort the array using quicksort. */
    
    cmergesort(arr, 0, numbersCount-1);
    
    /* Print the sorted array. */
    
    printf("Sorted array:\n");
    
    quicksortPrintIntegers(arr, numbersCount);
    
    /* Free the memory dynamically allocated. */
    
    free(arr);
    
}

