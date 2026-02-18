#ifndef SNAKE_H
#define SNAKE_H


#include "dir_queue.h"
#include "body_data_structure.h"
#include "body_part.h"
#include "grid.h"

typedef struct snake_head{
    int left, right, up, down; // keys to change direction
    int speed;
    int dirx, diry;

    double x, y;//retake look at it
    
    grid *grid;
    queue *direction_queue;
    body_data_structure *body_data_structure;
}snake_head;


#define LEFT 1;
#define RIGHT 3;
#define UP 5;
#define DOWN 2;
#define DT_TO_MOVE 500;

void init_snake(snake_head **snake);
void add_body_part(snake_head *snake);
void set_direction(snake_head **snake, int dalta_time);
void move_it(snake_head **snake, int dalta_time);

int get_x(body_part *snake_body);
int get_y(body_part *snake_body);
void set_cordinate(body_part *snake_body, int x, int y);
int normalize(int x);
void direction(snake_head **snake, int *dir);
void display_moves(snake_head *snake);
void progamma_exit(snake_head **snake);

#endif