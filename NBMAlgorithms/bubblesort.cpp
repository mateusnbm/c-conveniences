/*
 *
 * bubblesort.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 5/16/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#include "bubblesort.h"

/*
 *
 * Sorts an array of integers in-place using the Bubblesort algorithm.
 *
 * @param arr - The array of integers.
 * @param size - The size of the array.
 *
 */

void bubblesort(int arr[], int size) {

    int i, aux, exchange;

    do {

        exchange = 0;

        for (i = 0; i < (size-1); i++) {

            if (arr[i] > arr[i+1]) {

                exchange = 1;
                aux = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = aux;

            }

        }

    } while (exchange == 1);

}
