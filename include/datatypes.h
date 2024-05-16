#ifndef datatypes
#define datatypes

struct node {
  int vertex;
  struct node* next;
  int accessCounter;
};

struct Graph {
  int numVertices;
  struct node** adjLists;
};

struct QNode {
  int data;
  struct QNode* next;
};

struct Queue {
  struct QNode* head;
  int size;
};
struct Edge {
  struct node* vertex1;
  struct node* vertex2;
  int sum;
};

#endif
