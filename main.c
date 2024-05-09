#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "datatypes.h"

void bfs(struct Graph graph,int S,int D,int V,int *spLength, int *numOfsps){
    int visited[V] ;
    int dist[V];
    int nodeNum ;
    struct node *curr_node = malloc(sizeof(struct node));

    dist[S-1] = 0;
    struct Queue *queue = QInit();
    insert(queue,S);

    while(queue->head->next != NULL){
        nodeNum = delete(queue);
        if(visited[nodeNum-1] == 0){
            visited[nodeNum-1] = 1;
            
            if(graph.adjLists[nodeNum-1] != NULL){
                curr_node = graph.adjLists[nodeNum-1]->next;
                while(curr_node != NULL){
                    if(visited[curr_node->vertex-1] == 0){
                        insert(queue,curr_node->vertex);
                        dist[curr_node->vertex - 1] = dist[nodeNum] + 1;
                    }
                    curr_node = curr_node->next;
                }  
            }   
        }
    }

    *spLength = dist[D-1] ;
}


int main() {
    int numVertices = 0;
    int num1 = 0, num2 = 0;
    char filename[] = "edgelists/Erdos.edgelist";
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);

    while(fscanf(file,"%d %d\n", &num1, &num2)) {
        // Process the numbers here
        printf("%d %d\n", num1, num2);
        addEdge(graph, num1, num2);
    }
    printf("%d %d\n", num1, num2);
    fclose(file);

    //printGraph(graph);

    int spLength;
    int numOfsps;

    bfs(*graph,1,6927,numVertices,&spLength,&numOfsps);

    printf("The sp length from 1 to 6927 is: %d\n",spLength);

    return 0;
} 
