/*
 *
 * quicksort.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 3/16/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "quicksort.h"

/*
 *
 * Choses a pivot and places smaller numbers to the left of it and bigger numbers to the right.
 *
 * @param arr - The array of integers.
 * @param i0 - The lower bound of the range of integers that should be sorted.
 * @param iX - The upper bound of the range of integers that should be sorted.
 *
 * @return - The index of the pivot if the array was properly sorted.
 *
 */

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

/*
 *
 * Sorts an array of integers in-place using the Quicksort algorithm.
 *
 * @param arr - The array of integers.
 * @param i0 - The lower bound of the range of integers that should be sorted.
 * @param iX - The upper bound of the range of integers that should be sorted.
 *
 */

void quicksort(int arr[], int i0, int iX) {

    if (i0 < iX) {

        int pivotIndex = partition(arr, i0, iX);

        quicksort(arr, i0, (pivotIndex - 1));
        quicksort(arr, (pivotIndex + 1), iX);

    }

}
