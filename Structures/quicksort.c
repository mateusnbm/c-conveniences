//
//  quicksort.c
//  Structures
//
//  Created by Mateus Nunes de B Magalhaes on 3/16/17.
//  Copyright © 2017 mateusnbm. All rights reserved.
//

#include "quicksort.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int i0, int iX) {
    
    int aux;
    
    int originalPivotIndex = i0;
    int pivot = arr[i0];
    
    while (i0 < iX) {
        
        /* 
        
        Move the left index to the right until a number bigger than the pivot is found.
        
        */
        
        for (; arr[i0] <= pivot && i0 < iX; i0++);
        
        /* 
         
        Move the right index to the left until a number smaller than the pivot is found. 
         
        */
        
        for (; arr[iX] > pivot; iX--);
        
        /* 
         
        While the two indexes don't come across, keep swapping the numbers
        in order to store the ones smaller than the pivot to the left and the
        ones bigger than the pivot to the right.
         
        */
        
        if (i0 < iX) {
            
            aux = arr[i0];
            
            arr[i0] = arr[iX];
            arr[iX] = aux;
            
        }
        
    }
    
    arr[originalPivotIndex] = arr[iX];
    arr[iX] = pivot;
    
    return iX;
}

void quicksort(int arr[], int i0, int iX) {
    
    if (i0 < iX) {
        
        int pivotIndex = partition(arr, i0, iX);
        
        quicksort(arr, i0, (pivotIndex - 1));
        quicksort(arr, (pivotIndex + 1), iX);
        
    }
    
}

void printArray(int arr[], int size) {
    
    int i;
    
    for (i = 0; i < size; i++) {
        
        printf("%i\n", arr[i]);
        
    }
    
    printf("\n");
    
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
    
    printArray(arr, numbersCount);
    
    /* Sort the array using quicksort. */
    
    quicksort(arr, 0, numbersCount-1);
    
    /* Print the sorted array. */
    
    printf("Sorted array:\n");
    
    printArray(arr, numbersCount);
    
    /* Free the memory dynamically allocated. */
    
    free(arr);
    
}
