#ifndef functionPrototypes
#define functionPrototypes

//function prototypes for graphs
struct node* createNode(int v);

struct Graph* createAGraph(int vertices);

struct GraphPair splitGraph(struct Graph *graph, int *dist, int numVertices);

struct node* addEdge(struct Graph* graph, int s, int d);

void removeEdge(struct Graph* graph, int s, int d);

void printGraph(struct Graph* graph);

struct Graph* reorderGraph(struct Graph* graph, int newOrder[],int numVertices);

//function prototypes for fifo
struct Queue* QInit();

void QDestroy(struct Queue *queue);

void QInsert(struct Queue *queue, int data);

int QDelete(struct Queue *queue);

//Function prototypes cpl_sp

void mergePairs(struct pairs arr[], int l, int m, int r);

void mergeSortPairs(struct pairs arr[], int n);

int binomialCoeff(int n, int k);

int sum(int arr[], int n);

void nZeros(int **array,int n);

void nZerosPairs(struct pairs **array,int n);

int pathSearch(struct Graph graph,int **dist,struct parents **par,int S,int V, int Dest);

struct pairs cpl_sp(struct Graph graph,int V,double *cpl);

void CountTotalEdges(struct pairs **edgeArray,struct parents *par,int S,int V);

#endif