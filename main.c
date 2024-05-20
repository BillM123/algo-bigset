#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependencies/include/datatypes.h"
#include "dependencies/include/prototypes.h"


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

    for(numEdges = 0; fscanf(file, "%d %d\n", &num1,&num2); numEdges++){
        addEdge(graph, num1, num2);
        addEdge(graph, num2, num1);
    }
    
    fclose(file);
    //printGraph(graph);

    double cpl;
    cpl_sp(*graph,numVertices,&cpl);
    printf("The CPL is: %lf\n", cpl);

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
    system("leaks executablename");
    return 0;
    
}
