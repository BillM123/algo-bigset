#ifndef datatypes
#define datatypes

struct node {
  int vertex;
  struct node* next;
  int spNum;
};

struct Graph {
  int numVertices;
  struct node** adjLists;
};

struct QNode {
  struct node* data;
  struct QNode* next;
};

struct Queue {
  struct QNode* head;
  int size;
};

#endif
//