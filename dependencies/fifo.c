//A small API for fifo queue

#include <stdlib.h>
#include "include/datatypes.h"
#include "include/prototypes.h"

//Some is used from:
//https://gist.github.com/ryankurte/61f95dc71133561ed055ff62b33585f8

struct Queue* QInit(){
    struct Queue *queue = malloc(sizeof(struct Queue));
    
    //empty list item
    struct QNode *sentinel = malloc(sizeof(struct QNode));

    queue->head = sentinel;
    queue->tail = sentinel;
    sentinel->next = NULL;

    return queue;
}

void QDestroy(struct Queue *queue){
    struct QNode *curr;
    struct QNode *prev;

    curr = queue->head;
    while(curr != NULL){
        prev = curr;
        curr = prev->next;
        free(prev);
    }
    free(queue);
}
void QInsert(struct Queue *queue, int data){
    struct QNode *newNode = malloc(sizeof(struct QNode));

    newNode->data = data;
    //newNode->next = queue->head->next;
    newNode->next = NULL;
    //queue->head->next = newNode;
    queue->tail->next = newNode;
    queue->tail = newNode;
    queue->size++;
}

int QDelete(struct Queue *queue){
    struct QNode *tmp = queue->head->next;

    if(tmp != NULL){
        queue->head->next = tmp->next;
        if(tmp == queue->tail){
            queue->tail = queue->head;
        }
        int data = tmp->data;
        free(tmp);
        return data;
    }
    return -1;
}