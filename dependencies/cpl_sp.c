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

    printf("$$$ %d ### (%d,%d)\n", mostSPs, mostSPsPair[0], mostSPsPair[1]);

    free(dist);
    free(par);
    free(tmp);

    return mostUsedEdge;
}
