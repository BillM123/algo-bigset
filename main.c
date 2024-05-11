#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "datatypes.h"
#define MAX_EDGES 12000

//https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
// Returns value of Binomial Coefficient C(n, k)
int binomialCoeff(int n, int k)
{
    // Base Cases
    if (k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;
 
    // Recur
    return binomialCoeff(n - 1, k - 1)
           + binomialCoeff(n - 1, k);
}


void bfs(struct Graph graph,int S,int D,int V,int *spLength, int *numOfsps){
    int dist[V] ;
    int nodeNum ;
    
    struct node *curr_node = malloc(sizeof(struct node));

    memset(dist, 0, V*sizeof(int));
    *spLength = 0;
    *numOfsps = 0;

    struct Queue *queue = QInit();
    insert(queue,S);

    while(queue->head->next != NULL){
        nodeNum = delete(queue);
        
        if(graph.adjLists[nodeNum-1] != NULL){
            curr_node = graph.adjLists[nodeNum-1];
            
            while(curr_node != NULL){
                if(curr_node->vertex == D && ((dist[nodeNum-1] + 1 ) == dist[D-1] || dist[D-1] == 0)){
                    (*numOfsps)++; 
                }
                if(dist[curr_node->vertex-1] == 0){
                    insert(queue,curr_node->vertex);
                    dist[curr_node->vertex - 1] = dist[nodeNum-1] + 1;
                    //Σημείωση: δεν ειμαι σιγουρος πως αυτο λειτουργει, 
                    //αλλα φανταζομαι ειναι ενας απο τους δυο τροπους:
                    //1: Καινουργιος κομβος μπαινει στην ουρα μονο οταν ειναι κομματι του sp
                    //σε αυτή τη περίπτση αυτό μάλλον λειτουργαί
                    //2: Καθε καινουργιος κομβος που βρισκουμε μπαινει στην ουρα
                    //Οποτε θα πρεπει να μειονουμε το counter οταν διαβαζουμε/βγαζουμε το στοιχειο απο την ουρα
                    //Οποτε βαλε curr_node->accessCounter--; κάτω απο το nodeNum = delete(queue);
                    //(αν και θα πρεπει να αλλαξουμε τη delete να δινει pointer στο edge σε αυτη τη περιπτωση)
                    //PS: οταν γραφω τα παραπανω ειναι 12 το βραδυ, σρυ (+ρωτα αν θες) αν δεν βγαζουν τα παραπανω νοημα
                    curr_node->accessCounter++;
                }
                curr_node = curr_node->next;
            }  
        }   
    }

    *spLength = dist[D-1];
    QDestroy(queue);
    free(curr_node);
}

int *cpl_sp(struct Graph graph,int V,double *cpl){
    int i,j,k = 0;
    int spLength;
    int *numOfsps = malloc(binomialCoeff(V,2) * sizeof(int));
    int sumOfSps = 0 ;

    for(i=1; i<V; i++){
        for(j=i+1; j<V; j++){
            bfs(graph,i,j,V,&spLength,&numOfsps[k]);
            sumOfSps += spLength;
            k++;
        }
    }

    *cpl = (double)sumOfSps / binomialCoeff(V,2);

    return numOfsps;

}


int main() {
    int numVertices = 0;
    int numEdges = 0;
    int num1 = 0, num2 = 0;
    char blank;
    struct node*** edgeMatrix;
    struct node**  edgeList;
    char filename[] = "edgelists/karate.edgelist";
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d\n", &numVertices);
    struct Graph *graph = createAGraph(numVertices);

    //memory allocation for the matrix for rows
    edgeMatrix = (struct node ***)malloc(numVertices * sizeof(int **));
    //for columns
    for (int i = 0; i < numVertices; i++) {
        edgeMatrix[i] = (struct node **)malloc(numVertices * sizeof(int *));
        //Init of individual elements
        for (int j = 0; j < numVertices; j++){
            edgeMatrix[i][j] = NULL;
        }
    }

   while(fscanf(file, "%d %c%d\n", &num1, &blank, &num2)){
        //Note: We need to sort all the edges so we need them to be indexed
        //In the matrix, i j and j i elements represent the same graph due to the
        //nature of the input (it gives both i j and j i as different edges)
        //allocate memory only for non-empty matrix spaces
        edgeMatrix[num1][num2] = (struct node *)malloc(sizeof(struct node)); //SEGMENTATION FAULT
        edgeMatrix[num1][num2] = addEdge(graph, num1, num2);
        numEdges++;
    }
    fclose(file);
    printGraph(graph);

    int Source ;
    int Destination ;

    printf("Input to node to find their SP Length and number of SPs: ");
    scanf("%d %d",&Source, &Destination);

    int spLength;
    int numOfsps;

    //double cpl;
    //int *arraySPs=cpl_sp(*graph,numVertices,&cpl);
    //printf("The CPL is: %d\n", cpl);

    bfs(*graph,Source,Destination,numVertices,&spLength,&numOfsps);

    printf("The sp length from %d to %d is: %d and we have: %d SPs\n",Source,Destination,spLength,numOfsps);

    //NOTE: This should be put below the cpl_sp call
    //Initialize the edgeList
    edgeList = malloc((numEdges/2 + 1)*sizeof(int *));

    //Convert the edgeMatrix to an edgeList to be able to sort
    for(int i = 0, k = 0; i < numVertices; i++){
        for(int j = 0; j < i; j++){
            if(edgeMatrix[i][j] != NULL){
                //Note: Non directional graph: gurantee that edgeMatrix[j][i] also exists 
                edgeMatrix[i][j]->accessCounter+= edgeMatrix[j][i]->accessCounter;

                edgeList[k] = malloc(sizeof(struct node));
                edgeList[k] = edgeMatrix[i][j];
            }
        }
    }

    //Set free the edgematrix
    for(int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            if(edgeMatrix[i][j] != NULL){
                free(edgeMatrix[i][j]);
            }
        }
        free(edgeMatrix[i]);
    }
    free(edgeMatrix);

    return 0;
}
