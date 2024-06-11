#ifndef datatypes
#define datatypes

struct parents{
  int parent;
  struct parents *nextParent;
};

struct pairs{
  int numOfsps;
  int i;
  int j;
};

struct node {
  int vertex;
  struct node* next;
};

struct Graph {
  int numVertices;
  struct node** adjLists;
};

struct GraphPair {
  struct Graph *biggerGraph;
  struct Graph *smallerGraph;
};

struct QNode {
  int data;
  struct QNode* next;
};

struct Queue {
  struct QNode* head;
  struct QNode* tail;
  int size;
};
#endif
