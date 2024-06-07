#include <stdio.h>
#include <stdlib.h>
#include "include/datatypes.h"
#include "include/prototypes.h"

//Note: Initially got some functions from source:
//https://www.programiz.com/dsa/graph-adjacency-list
// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  if(vertices <= 0){
    return graph; //If number of vertices unclear, allow handling outside of function
  }
  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;
  return graph;
}

// Split graph
struct GraphPair splitGraph(struct Graph *graph, int *dist, int numVertices){
  struct Graph *graph1 ;
  struct Graph *graph2 ;
  struct GraphPair graphPair;

  int newOrder1[numVertices] ;
  int numVertices1 = 0;

  int newOrder2[numVertices] ;
  int numVertices2 = 0;

  for(int i = 0; i < numVertices; i++){
    if (dist[i] != 0){
      newOrder1[numVertices1] = i+1;
      numVertices1++;
    }
    else{
      newOrder2[numVertices2] = i+1;
      numVertices2++;
    }
  }

  graph1 = reorderGraph(graph,newOrder1,numVertices1);
  graph2 = reorderGraph(graph,newOrder2,numVertices2);

  graph1->numVertices = numVertices1;
  graph2->numVertices = numVertices2;
  

  if(graph1->numVertices >= graph2->numVertices){
    graphPair.biggerGraph = graph1;
    graphPair.smallerGraph = graph2;
  }
  else{
    graphPair.biggerGraph = graph2;
    graphPair.smallerGraph = graph1;
  }
  return graphPair;
}

// Add edge
struct node* addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s-1];
  graph->adjLists[s-1] = newNode;
  return newNode;
}

// Remove an edge
void removeEdge(struct Graph* graph, int s, int d){
  struct node *tmpPrev = graph->adjLists[s-1];
  struct node *tmpNext = tmpPrev->next;

  //Note: If there exists only one node, this is 
  //the only possible note we could be looking for
  if(tmpPrev->vertex == d){
    graph->adjLists[s-1] = tmpNext;
    free(tmpPrev);
    return;
  }
  //printf("%d->", tmpPrev->vertex); fflush(stdout);
  //Note: Valid edge should be passed to function, 
  //      else expect a segfault
  while(tmpNext->vertex != d){ 
    //printf("%d->", tmpNext->vertex); fflush(stdout);
    tmpPrev = tmpPrev->next;
    tmpNext = tmpNext->next;
  }
  //printf("\n");
  tmpPrev->next = tmpNext->next;
  //tmpNext->next = NULL;
  free(tmpNext);
}


struct Graph* reorderGraph(struct Graph* graph, int newOrder[],int numVertices) {
    struct Graph* newGraph = createAGraph(numVertices);

    for (int i = 0; i < numVertices; i++) {
        int newIdx = newOrder[i];
        struct node* temp = graph->adjLists[newIdx-1];

        while (temp) {
            int newDestIdx = -1;
            for (int j = 0; j < numVertices; j++) {
                if (newOrder[j] == temp->vertex) {
                    newDestIdx = j;
                    break;
                }
            }
            addEdge(newGraph, i+1, newDestIdx+1);
            temp = temp->next;
        }
    }

    return newGraph;
}

// Print the graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    printf("\n Vertex %d\n: ", v+1);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

void freeGraph(struct Graph *graph){
  for(int i =0; i < graph->numVertices; i++){
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
}
