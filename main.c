#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "datatypes.h"



int main() {
    int numVertices = 0;
    int num1 = 0, num2 = 0;
    char blank;
    char filename[] = "edgelists/Erdos.edgelist";
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);

    while(fscanf(file, "%d %c%d\n", &num1, &blank, &num2)) {
        // Process the numbers here
        printf("%d %d\n", num1, num2);
        addEdge(graph, num1, num2);
    }
    printf("%d %d\n", num1, num2);
    fclose(file);

    printGraph(graph);

    return 0;
} 
