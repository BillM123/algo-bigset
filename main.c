#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
   
   #if defined(Erdos) || defined(grid)
   while(fscanf(file, "%d %d\n", &num1,&num2)){
        addEdge(graph, num1, num2);
        addEdge(graph, num2, num1);
    }
    #endif

    #if defined(karate) || defined(dim)
        char blank;
        while(fscanf(file, "%d %c%d\n", &num1,&blank,&num2)){
        addEdge(graph, num1, num2);
    }
    #endif 
    fclose(file);
    //printGraph(graph);

    double cpl;
    cpl_sp(*graph,numVertices,&cpl);
    printf("The CPL is: %lf\n", cpl);

    return 0;
}
