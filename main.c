#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/prototypes.h"
#include "include/datatypes.h"
#define MAX_EDGES 12000

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
    int numVertices = 0;
    int num1 = 0, num2 = 0;
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);
   
   
    while(fscanf(file, "%d %d\n", &num1,&num2)){
        addEdge(graph, num1, num2);
        addEdge(graph, num2, num1);
    }
    
    fclose(file);
    //printGraph(graph);

    double cpl;
    cpl_sp(*graph,numVertices,&cpl);
    printf("The CPL is: %lf\n", cpl);

    return 0;
}
