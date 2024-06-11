#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "include/datatypes.h"
#include "include/prototypes.h"
#define TASK_SIZE 100

// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }

void mergeSortAux(struct pairs *X, int n,struct pairs *tmp)
{
   int i = 0;
   int j = n/2;
   int ti = 0;

   while (i<n/2 && j<n) {
      if (X[i].numOfsps > X[j].numOfsps) {
         tmp[ti] = X[i];
         ti++; i++;
      } else {
         tmp[ti] = X[j];
         ti++; j++;
      }
   }
   while (i<n/2) { /* finish up lower half */
      tmp[ti] = X[i];
      ti++; i++;
   }
   while (j<n) { /* finish up upper half */
      tmp[ti] = X[j];
      ti++; j++;
   }
   memcpy(X, tmp, n*sizeof(struct pairs));
} 

void mergeSort(struct pairs *X, int n, struct pairs *tmp)
{
   if (n < 2) return;

   #pragma omp task shared(X) if (n > TASK_SIZE)
   mergeSort(X, n/2, tmp);

   #pragma omp task shared(X) if (n > TASK_SIZE)
   mergeSort(X+(n/2), n-(n/2), tmp + n/2);

   #pragma omp taskwait
   mergeSortAux(X, n, tmp);
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
            
            curr_node = curr_parent.parent;
            curr_parent = par[curr_node-1];
        }
        
        ((*edgeArray)+curr_parent.parent-1)[curr_node-1].numOfsps++;
        ((*edgeArray)+curr_parent.parent-1)[curr_node-1].i = curr_parent.parent;
        ((*edgeArray)+curr_parent.parent-1)[curr_node-1].j = curr_node;

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
                    // Return if we've reached the target node
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
        //Assumes there is no vertex 0
        pathSearch(graph,&dist,&par,i,V, 0);
        nZeros(&dist,i);
        sumOfSps += sum(dist,V);

        CountTotalEdges(&edgeArray,par,i,V);
        //for (int j = i+1; j <= V; j++){
        //    countEdgesPath(&edgeArray, par, i, j);
        //} //Commented code makes CountTotalEdges obsolete

        

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

   //clock_t start, end;
   //double cpu_time_used;
   //start = clock();
   struct pairs *tmp = malloc(V*V * sizeof(struct pairs));

    double begin = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSort(edgeArray,V*V,tmp);
    }
    double end = omp_get_wtime();
    //end = clock();
    //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f",end-begin);
    *cpl = (double)sumOfSps / binomialCoeff(V,2);

    mostUsedEdge = edgeArray[0];

    free(edgeArray);
    free(dist);
    free(par);
    free(tmp);

    return mostUsedEdge;
}
