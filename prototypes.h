#ifndef functionPrototypes
#define functionPrototypes

//function prototypes for graphs
struct node* createNode(int v);

struct Graph* createAGraph(int vertices);

void addEdge(struct Graph* graph, int s, int d);

void printGraph(struct Graph* graph);

//function prototypes for fifo
struct Queue* QInit();

void QDestroy(struct Queue *queue);

void insert(struct Queue *queue, int data);

int delete(struct Queue *queue);

#endif