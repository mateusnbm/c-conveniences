/*
 * mergesort.c
 * Structures
 *
 * Created by Mateus Nunes de B Magalhaes on 5/16/19.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include "mergesort.h"

void cmerge(int arr[], int i0, int iC, int iX) {
    
    int s1 = i0;
    int s2 = iC + 1;
    int aux = 0;
    int len = iX - i0 + 1;
    
    int * arrcpy = (int *) malloc(sizeof(int)*len);
    
    while (s1 <= iC && s2 <= iX) {
        
        if (arr[s1] < arr[s2]) {
            
            arrcpy[aux] = arr[s1++];
            
        } else {
            
            arrcpy[aux] = arr[s2++];
            
        }
        
        aux++;
        
    }
    
    while (s1 <= iC) { arrcpy[aux++] = arr[s1++]; }
    while (s2 <= iX) { arrcpy[aux++] = arr[s2++]; }
    
    for (aux = i0; aux <= iX; aux++) {
        
        arr[aux] = arrcpy[aux-i0];
        
    }
    
    free(arrcpy);
    
}

void cmergesort(int arr[], int i0, int iX) {
    
    if (i0 < iX) {
        
        int central = (i0 + iX)/2;
        
        cmergesort(arr, i0, central);
        cmergesort(arr, (central + 1), iX);
        cmerge(arr, i0, central, iX);
        
    }
    
}
