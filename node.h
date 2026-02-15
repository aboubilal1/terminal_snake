#ifndef NODE_H
#define NODE_H

#include <stdio.h>

typedef struct node{
    int data;
    struct node* next;
} node;

#endif