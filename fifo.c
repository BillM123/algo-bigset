#include <stdlib.h>
#include <assert.h>
#include "datatypes.h"
#include "prototypes.h"

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    void** data;
} queue_t;

void* queue_read(queue_t *queue) {
    if (queue->tail == queue->head) {
        return NULL;
    }
    void* handle = queue->data[queue->tail];
    queue->data[queue->tail] = NULL;
    queue->tail = (queue->tail + 1) % queue->size;
    return handle;
}

int queue_write(queue_t *queue, void* handle) {
    // Note that empty is head==tail, thus only QUEUE_SIZE-1 entries may be used.
    if (((queue->head + 1) % queue->size) == queue->tail) {
        return -1;
    }
    queue->data[queue->head] = handle;
    queue->head = (queue->head + 1) % queue->size;
    return 0;
} 

//https://gist.github.com/ryankurte/61f95dc71133561ed055ff62b33585f8

struct Queue* QInit(){
    struct Queue *queue = malloc(sizeof(struct Queue));
    
    //empty list item
    struct QNode *sentinel = malloc(sizeof(struct QNode));

    queue->head = sentinel;
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
void insert(struct Queue *queue, void *data){
    struct QNode *newNode = malloc(sizeof(struct QNode));

    newNode->data = data;
    newNode->next = queue->head->next;
    queue->head->next = newNode;
    queue->size++;
}
void* delete(struct Queue *queue){
    struct QNode *curr;
    struct QNode *prev;
    void *data;

    curr = queue->head;
    while(curr->next != NULL){
        prev = curr;
        curr = prev->next; 
    }
    data = curr->data;
    free(curr);
    prev->next = NULL;
    return data;
}