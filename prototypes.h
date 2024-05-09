#ifndef functionPrototypes
#define functionPrototypes

//function prototypes for graphs
struct node* createNode(int v);

struct Graph* createAGraph(int vertices);

struct node* addEdge(struct Graph* graph, int s, int d);

void printGraph(struct Graph* graph);

//function prototypes for fifo
struct Queue* QInit();

void QDestroy(struct Queue *queue);

void insert(struct Queue *queue, void *data);

void* delete(struct Queue *queue);

#endif