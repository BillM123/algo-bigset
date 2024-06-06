#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/datatypes.h"
#include "include/prototypes.h"

// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }
 
 
/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSortPairs(struct pairs arr[], int n)
{
   int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
   int left_start; // For picking starting index of left subarray
                   // to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = min(left_start + curr_size - 1, n-1);
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           mergePairs(arr, left_start, mid, right_end);
       }
   }
}
 
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void mergePairs(struct pairs arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    struct pairs *L = malloc(n1*sizeof(struct pairs));
    struct pairs *R = malloc(n2*sizeof(struct pairs));
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].numOfsps >= R[j].numOfsps)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
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


void countEdgesPath(struct pairs **edgeArray,struct parents *par,int S,int D){
    int curr_node = D;
    struct parents curr_parent,initialParent = par[curr_node-1];

    while(1){
        curr_node = D;
        curr_parent = initialParent;
        while(curr_parent.parent != S){
            ((*edgeArray)+curr_parent.parent-1)[curr_node-1].numOfsps++;
            ((*edgeArray)+curr_parent.parent-1)[curr_node-1].i = curr_parent.parent;
            ((*edgeArray)+curr_parent.parent-1)[curr_node-1].j = curr_node;
            //printf("(%d %d) +1\n",(curr_parent.parent-1),curr_node-1);
            //((*edgeArray)+curr_node-1)[curr_parent.parent-1]++;
            curr_node = curr_parent.parent;
            curr_parent = par[curr_node-1];
        }
        ((*edgeArray)+curr_parent.parent-1)[curr_node-1].numOfsps++;
        ((*edgeArray)+curr_parent.parent-1)[curr_node-1].i = curr_parent.parent;
        ((*edgeArray)+curr_parent.parent-1)[curr_node-1].j = curr_node;
        //printf("(%d %d) +1\n",(curr_parent.parent-1),curr_node-1);
        //((*edgeArray)+curr_node-1)[curr_parent.parent-1]++;

        if(initialParent.nextParent == NULL){
            break;
        }
        initialParent = *(initialParent.nextParent) ;
    }
}

void CountTotalEdges(struct pairs **edgeArray,struct parents *par,int S,int V){
    int i =0;

    for(i=S+1; i<=V; i++){
        countEdgesPath(edgeArray,par,S,i);
    }
}


int pathSearch(struct Graph graph,int **dist,struct parents **par,int S,int V, int Dest){
    int nodeNum ;
    
    struct node *curr_node;

    int i;
    for(i=0; i<V; i++){
        (*dist)[i] = 0;
    }

    struct Queue *queue = QInit();
    QInsert(queue,S);
    (*par)[S-1].parent = S;
    (*par)[S-1].nextParent = NULL;

    while(queue->head->next != NULL){
        nodeNum = QDelete(queue);
        if(graph.adjLists[nodeNum-1] != NULL){
            curr_node = graph.adjLists[nodeNum-1];
            
            while(curr_node != NULL){
                if((*dist)[curr_node->vertex-1] == 0 && (curr_node->vertex) != S){
                    QInsert(queue,curr_node->vertex);
                    (*dist)[curr_node->vertex - 1] = (*dist)[nodeNum-1] + 1;

                    (*par)[curr_node->vertex-1].parent = nodeNum;
                    (*par)[curr_node->vertex-1].nextParent = NULL;
                }
                else if((*dist)[curr_node->vertex-1] == (*dist)[nodeNum-1] + 1){
                    struct parents *tmp = malloc(sizeof(struct parents));
                    tmp->nextParent = (*par)[curr_node->vertex-1].nextParent; 
                    (*par)[curr_node->vertex-1].nextParent = tmp;
                    (*par)[curr_node->vertex-1].nextParent->parent = nodeNum;
                }
                if (curr_node != NULL && (*dist)[curr_node->vertex - 1] == (*dist)[nodeNum - 1] + 1 && curr_node->vertex == Dest) {
                    //break; // Exit the loop when we've reached the target node
                    QDestroy(queue);
                    return 1;
                }

                curr_node = curr_node->next;
            } 
        }   
    }

    QDestroy(queue);
    return 0;
}

struct pairs cpl_sp(struct Graph graph,int V,double *cpl){
    int *dist = malloc(V * sizeof(int));
    struct parents *par = malloc(V*sizeof(struct parents));
    struct pairs *edgeArray = calloc(V*V,sizeof(struct pairs)); 
    struct pairs mostUsedEdge;

    int sumOfSps = 0 ;
    int i;

    par[0].parent = -1;

    for(i=1; i<=V; i++){
        //printf("\n%d\n",i);
        //Assumes there is no vertex 0
        pathSearch(graph,&dist,&par,i,V, 0);
        nZeros(&dist,i);
        sumOfSps += sum(dist,V);

        CountTotalEdges(&edgeArray,par,i,V);
        //for (int j = i+1; j <= V; j++){
        //    countEdgesPath(&edgeArray, par, i, j);
        //} Commented code makes CountTotalEdges obsolete
        

        struct parents *temp_prev, *temp_next ;

        for(int k=0; k<V; k++){
            temp_prev = par[k].nextParent;
            while(temp_prev != NULL){
                temp_next = temp_prev->nextParent;
                free(temp_prev);
                temp_prev=temp_next;
            }
        }
    }
    mergeSortPairs(edgeArray,(V*V));
    *cpl = (double)sumOfSps / binomialCoeff(V,2);

    mostUsedEdge = edgeArray[0];

    free(edgeArray);
    free(dist);
    free(par);

    return mostUsedEdge;
}
