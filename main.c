#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/prototypes.h"
#include "include/datatypes.h"
#define MAX_EDGES 12000

//https://www.geeksforgeeks.org/merge-sort/
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(struct Edge **arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    struct Edge *L[n1], *R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        *L[i] = *arr[l + i];
    for (j = 0; j < n2; j++)
        *R[j] = *arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i]->vertex1->accessCounter + L[i]->vertex2->accessCounter 
        <= R[j]->vertex1->accessCounter + R[j]->vertex2->accessCounter) {
            *arr[k] = *L[i];
            i++;
        }
        else {
            *arr[k] = *R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        *arr[k] = *L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        *arr[k] = *R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(struct Edge **arr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
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

//This function zeros the first n cell of an int array
void nZeros(int **array,int n){
    int i;

    for(i=0; i<n; i++){
        *(array[0]) = 0;
    }     
}


int **pathSearch(struct Graph graph,int S,int V){
    int *dist = malloc(V*sizeof(int)) ;
    int *numOfsps = malloc(V*sizeof(int));
    int **returnValues = malloc(2*sizeof(int*));
    int nodeNum ;
    
    struct node *curr_node = malloc(sizeof(struct node));

    memset(dist,0,V*sizeof(int));
    memset(numOfsps,0,V*sizeof(int));

    struct Queue *queue = QInit();
    insert(queue,S);

    while(queue->head->next != NULL){
        nodeNum = delete(queue);
        if(graph.adjLists[nodeNum-1] != NULL){
            curr_node = graph.adjLists[nodeNum-1];
            
            while(curr_node != NULL){
                if(dist[curr_node->vertex-1] == 0 && (curr_node->vertex) != S){
                    insert(queue,curr_node->vertex);
                    dist[curr_node->vertex - 1] = dist[nodeNum-1] + 1;
                    numOfsps[curr_node->vertex-1]++;
                }
                else if(dist[curr_node->vertex-1] == dist[nodeNum-1] + 1){
                    numOfsps[curr_node->vertex-1]++;
                }
                curr_node = curr_node->next;
            }  
        }   
    }

    returnValues[0] = dist;
    returnValues[1] = numOfsps;

    QDestroy(queue);
    free(curr_node);

    return returnValues;
}

void cpl_sp(struct Graph graph,int V,double *cpl){
    int i;
    int **pathSearchReturn;
    int sumOfSps = 0 ;

    for(i=1; i<=V; i++){
        pathSearchReturn = pathSearch(graph,i,V);
        nZeros(&pathSearchReturn[0],i);
        sumOfSps += sum(pathSearchReturn[0],V);
        
    }

    *cpl = (double)sumOfSps / binomialCoeff(V,2);

}


int main(int argc, char* argv[]) {
    int numVertices = 0, numEdges;
    int num1 = 0, num2 = 0;
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);
    struct Edge **edgeList = malloc(sizeof(struct Edge*));
   
    for(numEdges = 0; fscanf(file, "%d %d\n", &num1,&num2); numEdges++){
        edgeList[numEdges] = malloc(sizeof(struct Edge));
        edgeList[numEdges]->vertex1 = addEdge(graph, num1, num2);
        edgeList[numEdges]->vertex2 = addEdge(graph, num2, num1);
    }
    
    fclose(file);
    //printGraph(graph);

    double cpl;
    cpl_sp(*graph,numVertices,&cpl);
    printf("The CPL is: %lf\n", cpl);
    mergeSort(edgeList, 0, numEdges-1);
    printf("Most used edge:%d<->%d with %d uses\n", 
    edgeList[0]->vertex1->vertex, edgeList[0]->vertex2->vertex,
    edgeList[0]->vertex1->accessCounter + edgeList[0]->vertex2->accessCounter);

    for(int i = 0; i < numEdges; i++){
        free(edgeList[numEdges]);
    }//Note: each edge could be free'd when removed
    free(graph);
    free(edgeList);
    return 0;
}
