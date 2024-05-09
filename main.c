#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "datatypes.h"
#define MAX_EDGES 12000


int main() {
    int numVertices = 0;
    int num1 = 0, num2 = 0;
    char blank;
    struct node* edgeList[MAX_EDGES];
    char filename[] = "edgelists/Erdos.edgelist";
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);

    for(int i = 0; fscanf(file, "%d %c%d\n", &num1, &blank, &num2); i++) {
        // Process the numbers here
        printf("%d %d\n", num1, num2);
        edgeList[i] = addEdge(graph, num1, num2);
    }

    printf("%d %d\n", num1, num2);
    fclose(file);

    printGraph(graph);

    return 0;
} //
