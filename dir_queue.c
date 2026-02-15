#include "dir_queue.h"

void init_queue(queue **q){
    // printf("5 Initializing queue.\n");
    *q = malloc(sizeof(queue));
    if (!(*q)) return;
    // printf("5.1 Queue initialized.\n");
    (*q)->head = NULL;
    (*q)->tail = NULL;
}

int empty_queue(queue *q){
    if (!q){
        return 1;
    }
    return q->head == NULL;
}

int one_element_queue(queue *q){
    if (!q){
        return 1;
    }
    return q->head == q->tail;
}

void queue_in(queue *q, int data){
    node *n = (node*)malloc(sizeof(node));
    if (!n) return;
    n->data = data;
    n->next = NULL;

    if(empty_queue(q)){
        q->head = n;
        q->tail = n;
    }else{
        q->tail->next = n;
        q->tail = n;
    }
}

void unqueue(queue *q, int *data){
    if (empty_queue(q)){
        return;
    }
    node *n = q->head;
    if (!n) return;
    *data = n->data;
    q->head = q->head->next;
    free(n);
}

void head_queue(queue *q, int *data){
    if (empty_queue(q)){
        return;
    }
    *data = q->head->data;
}

void tail_queue(queue *q, int *data){
    if (empty_queue(q)){
        return;
    }
    *data = q->tail->data;
}
