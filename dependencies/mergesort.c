#include <stdio.h>
#include <stdlib.h>
#include "include/datatypes.h"
#include "include/prototypes.h"

#define CUTOFF 7  // Threshold for switching to insertion sort



// Merge function to merge two sorted subarrays
void merge(struct pairs arr[], struct pairs aux[], int lo, int mid, int hi) {
    //printf("\n\n--||BEGIN MERGE DEBUG||--\n\n");
    //printf("hi:%d lo:%d mid:%d\n", hi, lo, mid);
    // Copy to aux[]
    for (int k = lo; k <= hi; k++) {
        aux[k] = arr[k];
        //printf("%d\n", aux[k].numOfsps);
    }
    //printf("\n\n");
    //printf("merge\n");
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid){
            arr[k] = aux[j++];
        } 
        else if (j > hi){
            arr[k] = aux[i++];
        } 
        else if(aux[j].numOfsps < aux[i].numOfsps) {
            arr[k] = aux[j++];
        } 
        else{
            arr[k] = aux[i++];
        } 
        //printf("%d\n", arr[k].numOfsps);
    }
    //printf("\n\n--||END MERGE DEBUG||--\n\n");
}

// Insertion sort for small subarrays
void insertionSort(struct pairs arr[], int lo, int hi) {
    //printf("\n\n--||BEGIN INSERT DEBUG||--\n\n");
    //printf("hi:%d lo:%d\n", hi, lo);
    for (int i = lo; i <= hi; i++) {
        for (int j = i; j > lo && arr[j].numOfsps < arr[j - 1].numOfsps; j--) {
            struct pairs temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            //printf("j-1:%d j:%d\n", arr[j-1].numOfsps, arr[j].numOfsps);
        }
    }
    //printf("\n\n--||END INSERT DEBUG||--\n\n");
}

// Recursive merge sort function
void mergeSort(struct pairs arr[], struct pairs aux[], int lo, int hi) {
    if (hi <= lo) return;

    // Use insertion sort for small subarrays
    if (hi <= lo + CUTOFF - 1) {
        //printf("insertion sort\n");
        insertionSort(arr, lo, hi);
        return;
    }
    //printf("mergesort\n");
    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, aux, lo, mid);
    mergeSort(arr, aux, mid + 1, hi);
    if (arr[mid].numOfsps <= arr[mid + 1].numOfsps) return;  // Skip merge if already sorted
    merge(arr, aux, lo, mid, hi);
}

// Wrapper function to initialize auxiliary array and start merge sort
void sort(struct pairs arr[], int n) {
    struct pairs *aux = (struct pairs *)malloc(n * sizeof(struct pairs));
    if (aux == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    //printf("sort called\n");
    mergeSort(arr, aux, 0, n - 1);
    free(aux);
}

// Utility function to print array of struct pairss
void printArray(struct pairs arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i].numOfsps);
    }
    printf("\n");
}

