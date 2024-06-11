#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "dependencies/include/datatypes.h"
#include "dependencies/include/prototypes.h"


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

    for(int i = 0; i < numEdges; i++){
        free(edgeList[numEdges]);
    }//Note: each edge could be free'd when removed

    free(graph);
    free(edgeList);
    return 0;
}
