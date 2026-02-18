#ifndef DIR_QUEUE_H
#define DIR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct queue{
    node *head;
    node *tail;
} queue;

void init_queue(queue **q);
int empty_queue(queue *q);
int one_element_queue(queue *q);

void queue_in(queue *q, int data);
void unqueue(queue *q, int *data);

void head_queue(queue *q, int *data);
void tail_queue(queue *q, int *data);

#endif