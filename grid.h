#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>

#define HEAD '@'
#define BODY 'O'
#define EMPTY '.'

typedef struct grid{
    int sizeX, sizeY;
    int cursor_position_X, cursor_position_Y;
    char empty_cells_character;
    
    int **matrix;

    // FILE *fp;
}grid;

int init_grid(grid **g, int sizeX, int sizeY, char cells_character);
void print_grid(grid *g);
// void go_to_point(grid *g, int x, int y);
// void print_cell(char cells_character);
void set_point_in_grid(grid *g, int x, int y, char cells_character);

#endif