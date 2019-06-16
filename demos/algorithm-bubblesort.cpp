/*
 * algorithm-bubblesort.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 3/14/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "bubblesort.h"

int main(int argc, const char * argv[]) {
    
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
    
    for (i = 0; i < numbersCount; i++) {
        
        printf("%i ", arr[i]);
        
    }
    
    printf("\n");
    
    /* Sort the array using quicksort. */
    
    bubblesort(arr, numbersCount);
    
    /* Print the sorted array. */
    
    printf("Sorted array:\n");
    
    for (i = 0; i < numbersCount; i++) {
        
        printf("%i ", arr[i]);
        
    }
    
    printf("\n");
    
    /* Free the memory dynamically allocated. */
    
    free(arr);
    
    return 0;
    
}
