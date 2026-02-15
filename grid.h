#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>

#define HEAD '@'
#define BODY 'O'
#define EMPTY '.'

typedef struct grid{
    int sizeX, sizeY;
    int posX, posY;
    char empty_cells_type;
    
    int **matrix;

    FILE *fp;
}grid;

void init_grid(grid **g, int sizeX, int sizeY, char cells_type);
void print_grid(grid *g);
// void go_to_point(grid *g, int x, int y);
// void print_cell(char cells_type);
void set_point_in_grid(grid *g, int x, int y, char cells_type);

#endif