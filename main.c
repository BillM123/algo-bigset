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

    double cpl;
    cpl_sp(*graph,numVertices,&cpl);
    printf("The CPL is: %lf\n", cpl);

    analyseGraph(graph, numVertices);

    for(int i =0; i < numVertices; i++){
        struct node *tmpPrev = graph->adjLists[i];
        struct node *tmpNext;

        while (tmpPrev != NULL) {
            tmpNext = tmpPrev->next;
            free(tmpPrev);
            tmpPrev = tmpNext;
        }

    }
    free(graph->adjLists);
    free(graph);
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

    //there is no graph for a single vertes
    if(numVertices == 1){
        return;
    }

    while(1){
        MostUsedEdge = cpl_sp(*graph, numVertices, &cpl);

        //debug
        printf("Edge: %d<-->%d\n", MostUsedEdge.i, MostUsedEdge.j);
        printGraph(graph);

        //Remove the most used edge in each iter
        removeEdge(graph, MostUsedEdge.i, MostUsedEdge.j);
        removeEdge(graph, MostUsedEdge.j, MostUsedEdge.i);

        //Could tell us if graph is split into 2. Assumes dist gets init'd in pathSearch func.
        int isConnected = pathSearch(*graph,&dist,&par,MostUsedEdge.i,numVertices, MostUsedEdge.j);

        if(isConnected == 0){
            graphPair = splitGraph(graph, dist, numVertices);
            free(dist);
            free(par);
            analyseGraph(graphPair.biggerGraph, graphPair.biggerGraph->numVertices);
            analyseGraph(graphPair.smallerGraph, graphPair.smallerGraph->numVertices);
            return;
        }
    }
}
