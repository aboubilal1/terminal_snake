#ifndef SNAKE_H
#define SNAKE_H


#include "dir_queue.h"
#include "body_ds.h"
#include "body_part.h"
#include "grid.h"

typedef struct snake_head{
    int left, right, up, down;
    int speed;
    int dirx, diry;

    double x, y;//retake look at it
    
    grid *grid;
    queue *direction;
    body_ds *body_ds;
}snake_head;


#define LEFT 1;
#define RIGHT 3;
#define UP 5;
#define DOWN 2;
#define DT_TO_MOVE 500;

void init_snake(snake_head **head);
void add_body_part(snake_head *head);
void set_direction(snake_head **head, int dt);
void move_it(snake_head **head, int dt);

int get_x(body_part *s);
int get_y(body_part *s);
void set_cordinate(body_part *s, int x, int y);
int normalize(int x);
void direction(snake_head **head, int *dir);
void display_moves(snake_head *s, grid *g);
void progamma_exit(snake_head **s);

#endif