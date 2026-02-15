#ifndef BODY_PART_H
#define BODY_PART_H

#define HEAD '@'
#define BODY 'O'
#define EMPTY '.'

typedef struct body_part{
    int x, y;
    struct body_part *next;
}body_part;

#endif