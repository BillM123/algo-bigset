#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/datatypes.h"
#include "include/prototypes.h"

void mergePairs(struct pairs arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    struct pairs L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].numOfsps >= R[j].numOfsps) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSortPairs(struct pairs arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSortPairs(arr, l, m);
        mergeSortPairs(arr, m + 1, r);

        mergePairs(arr, l, m, r);
    }
}

//https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
// Returns value of Binomial Coefficient C(n, k)
int binomialCoeff(int n, int k)
{
    // Base Cases
    if (k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;
 
    // Recur
    return binomialCoeff(n - 1, k - 1)
           + binomialCoeff(n - 1, k);
}

//https://www.geeksforgeeks.org/program-find-sum-elements-given-array/
// function to return sum of elements
// in an array of size n
int sum(int arr[], int n)
{
    // base case
    if (n == 0) {
        return 0;
    }
    else {
        // recursively calling the function
        return arr[0] + sum(arr + 1, n - 1);
    }
}

//This function zeros the first n cells of an int array
void nZeros(int **array,int n){
    int i;

    for(i=0; i<n; i++){
        (*array)[i] = 0;
    }     
}

//This function zeros the first n cells of an struct pair array
void nZerosPairs(struct pairs **array,int n){
    int i;

    for(i=0; i<n; i++){
        (*array)[i].numOfsps = 0;
    }     
}


struct pairs *pathSearch(struct Graph graph,int **dist,int S,int V){
    
    struct pairs *numOfSPsArray = malloc(V*sizeof(struct pairs)) ;
    int nodeNum ;
    
    struct node *curr_node = malloc(sizeof(struct node));

    memset(*dist,0,V*sizeof(int));
    memset(numOfSPsArray,0,V*sizeof(struct pairs));

    struct Queue *queue = QInit();
    insert(queue,S);

    while(queue->head->next != NULL){
        nodeNum = QDelete(queue);
        if(graph.adjLists[nodeNum-1] != NULL){
            curr_node = graph.adjLists[nodeNum-1];
            
            while(curr_node != NULL){
                if((*dist)[curr_node->vertex-1] == 0 && (curr_node->vertex) != S){
                    insert(queue,curr_node->vertex);
                    (*dist)[curr_node->vertex - 1] = (*dist)[nodeNum-1] + 1;
                    numOfSPsArray[curr_node->vertex-1].numOfsps++;
                    numOfSPsArray[curr_node->vertex-1].i = S;
                    numOfSPsArray[curr_node->vertex-1].j = curr_node->vertex;
                }
                else if((*dist)[curr_node->vertex-1] == (*dist)[nodeNum-1] + 1){
                    numOfSPsArray[curr_node->vertex-1].numOfsps++;
                }
                curr_node = curr_node->next;
            }  
        }   
    }

    QDestroy(queue);
    free(curr_node);

    return numOfSPsArray;
}

void cpl_sp(struct Graph graph,int V,double *cpl){
    int *dist = malloc(V * sizeof(int));
    struct pairs *numOfSPsArray ;
    int sumOfSps = 0 ;
    int mostSPs = 0;
    int mostSPsPair[2] ;
    int i;


    for(i=1; i<=V; i++){
        numOfSPsArray = pathSearch(graph,&dist,i,V);

        nZeros(&dist,i);
        nZerosPairs(&numOfSPsArray,i);

        sumOfSps += sum(dist,V);
        mergeSortPairs(numOfSPsArray,0,V-1);

        if(numOfSPsArray[0].numOfsps >= mostSPs){
            mostSPs = numOfSPsArray[0].numOfsps;
            mostSPsPair[0] = numOfSPsArray[0].i;
            mostSPsPair[1] = numOfSPsArray[0].j;
        }
    }
    *cpl = (double)sumOfSps / binomialCoeff(V,2);

    printf("$$$ %d ### (%d,%d)\n", mostSPs, mostSPsPair[0], mostSPsPair[1]);

    free(dist);
}
