#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "dependencies/include/datatypes.h"
#include "dependencies/include/prototypes.h"

#define TASK_SIZE 100

void analyseGraph(struct Graph *graph);

int main(int argc, char* argv[]) {
    int numVertices = 0;
    int num1 = 0, num2 = 0;
    omp_set_dynamic(0);
    omp_set_num_threads(12);

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);

    while (fscanf(file, "%d %d\n", &num1, &num2) == 2) {
        addEdge(graph, num1, num2);
        addEdge(graph, num2, num1);
    }
    
    fclose(file);

    analyseGraph(graph);

    return 0;
    
}

void analyseGraph(struct Graph *graph){
    struct pairs MostUsedEdge = {0};
    struct GraphPair graphPair;
    double cpl = 0;
    //Note: if graph is split, every element in dist != 0 belongs to first graph
    //      every element in dist == 0 belongs to second graph
    int *dist = malloc(graph->numVertices * sizeof(int));
    struct parents *par = malloc(graph->numVertices*sizeof(struct parents));
    for(int i = 0; i < graph->numVertices; i++){
        par[i].nextParent = NULL;
    }

    //there is no graph for a single vertex
    if(graph->numVertices == 1){
        free(dist);
        free(par);
        freeGraph(graph);
        return;
    }

    while(1){
        //Analyse current graph
        MostUsedEdge = cpl_sp(*graph, graph->numVertices, &cpl);
        printf("\n(%d %d)\n",MostUsedEdge.i,MostUsedEdge.j);
        printf("The CPL is: %lf\n", cpl);
        struct parents *temp_prev, *temp_next ;

        //Remove the most used edge in each iter
        removeEdge(graph, MostUsedEdge.i, MostUsedEdge.j);
        removeEdge(graph, MostUsedEdge.j, MostUsedEdge.i);

        //Could tell us if graph is split into 2. Assumes dist gets init'd in pathSearch func.
        int isConnected = pathSearch(*graph,&dist,&par,MostUsedEdge.i,graph->numVertices, MostUsedEdge.j);
        dist[MostUsedEdge.i-1] = -1;

        //free parents
        for(int k=0; k<graph->numVertices; k++){
            temp_prev = par[k].nextParent;
            while(temp_prev != NULL){
                temp_next = temp_prev->nextParent;
                free(temp_prev);
                temp_prev=temp_next;
            }
            par[k].nextParent = NULL;
        }

        //enter if graph got split
        if(isConnected == 0){
            printf("\nThe graph split\n");
            graphPair = splitGraph(graph, dist,graph->numVertices);
            
            free(dist);
            free(par);
            freeGraph(graph);

            printf("\nBigger graph size: %d\n", graphPair.biggerGraph->numVertices);
            analyseGraph(graphPair.biggerGraph);
            printf("\nThe bigger graph finished running.\n");

            printf("\nSmaller graph size: %d\n", graphPair.smallerGraph->numVertices);
            analyseGraph(graphPair.smallerGraph);
            printf("\nThe smaller graph finished running.\n");
            return;
        }
        printf("\nNot split\n");
    }
}
