#include <stdio.h>
#include <stdlib.h>
#include "include/datatypes.h"
#include "include/prototypes.h"

//Note: Initially got functions from source:
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

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;
  return graph;
}

// Add edge
struct node* addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s-1];
  graph->adjLists[s-1] = newNode;
  return newNode;
}

void removeEdge(struct Graph* graph, int s, int d){
  struct node *tmpPrev = graph->adjLists[s];
  struct node *tmpNext = tmpPrev->next;

  //If there exists only one node, this is the only possible
  //note we could be looking for
  if(tmpNext == NULL){
    free(tmpPrev);
    return;
  }
  //Note: Valid edge should be passed to function, 
  //      else expect a segfault
  while(tmpNext->vertex != d){ 
    tmpPrev = tmpPrev->next;
    tmpNext = tmpNext->next;
  }
  tmpPrev->next = tmpNext->next;
  tmpNext->next = NULL;
  free(tmpNext);
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
