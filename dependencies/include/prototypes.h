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

void insert(struct Queue *queue, int data);

int QDelete(struct Queue *queue);

//Function prototypes cpl_sp

void mergePairs(struct pairs arr[], int l, int m, int r);

void mergeSortPairs(struct pairs arr[], int l, int r);

int binomialCoeff(int n, int k);

int sum(int arr[], int n);

void nZeros(int **array,int n);

void nZerosPairs(struct pairs **array,int n);

struct pairs *pathSearch(struct Graph graph,int **dist,int S,int V);

void cpl_sp(struct Graph graph,int V,double *cpl);

#endif