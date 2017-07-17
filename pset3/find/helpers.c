/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

void printArray(int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{   
    if (n > 1) {
        int mid = n / 2;
    
        if (values[mid] == value) {
            return true;
        }
    
        else if (value < values[mid]) {
            //printArray(values, mid);
            return search(value, values, mid);
        }
        else if (value > values[mid]) {
            //printf("%i\n", n);
            //printArray(&values[mid], mid);
            return search(value, &values[mid], mid+1);
        }
    }
    return (values[0] == value);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm - bubblesort
    for (int i = 0; i < n; i++) {
        int swaps = 0;
        for (int j = 0; j < n-1; j++) {;
            if(values[j] > values[j+1]) {
                int temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
                swaps += 1;
            }
        }
        if (swaps == 0) {
            // If we make a pass with no swaps, array is sorted
            return;
        }
    }
    return;
}

void printArray(int values[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%i, ", values[i]);
    }
    printf("\n");
}