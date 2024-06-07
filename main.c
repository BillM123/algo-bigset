#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependencies/include/datatypes.h"
#include "dependencies/include/prototypes.h"

void analyseGraph(struct Graph *graph, int numVertices);

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

    while (fscanf(file, "%d %d\n", &num1, &num2) == 2) {
        addEdge(graph, num1, num2);
        addEdge(graph, num2, num1);
    }
    
    fclose(file);
    //printGraph(graph);

    analyseGraph(graph, numVertices);

    return 0;
    
}

void analyseGraph(struct Graph *graph, int numVertices){
    struct pairs MostUsedEdge = {0};
    struct GraphPair graphPair;
    double cpl = 0;
    //Note: if graph is split, every element in dist != 0 belongs to first graph
    //      every element in dist == 0 belongs to second graph
    int *dist = malloc(numVertices * sizeof(int));
    struct parents *par = malloc(numVertices*sizeof(struct parents));
    for(int i = 0; i < numVertices; i++){
        par[i].nextParent = NULL;
    }

    //there is no graph for a single vertes
    if(numVertices == 1){
        free(dist);
        free(par);
        freeGraph(graph);
        return;
    }

    while(1){
        //Analyse current graph
        MostUsedEdge = cpl_sp(*graph, numVertices, &cpl);
        printf("\n(%d %d)\n",MostUsedEdge.i,MostUsedEdge.j);
        printf("The CPL is: %lf\n", cpl);
        struct parents *temp_prev, *temp_next ;

        //Remove the most used edge in each iter
        removeEdge(graph, MostUsedEdge.i, MostUsedEdge.j);
        removeEdge(graph, MostUsedEdge.j, MostUsedEdge.i);

        //Could tell us if graph is split into 2. Assumes dist gets init'd in pathSearch func.
        int isConnected = pathSearch(*graph,&dist,&par,MostUsedEdge.i,numVertices, MostUsedEdge.j);
        dist[MostUsedEdge.i-1] = -1;

        //free parents
        for(int k=0; k<numVertices; k++){
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
            graphPair = splitGraph(graph, dist, numVertices);
            
            free(dist);
            free(par);
            freeGraph(graph);

            printf("\nThe bigger graph is running...\n");
            analyseGraph(graphPair.biggerGraph, graphPair.biggerGraph->numVertices);
            printf("\nThe bigger graph finished running.\n");

            printf("\nThe smaller graph is running...\n");
            analyseGraph(graphPair.smallerGraph, graphPair.smallerGraph->numVertices);
            printf("\nThe smaller graph finished running.\n");
            return;
        }
        printf("\nNot split\n");
    }
}
