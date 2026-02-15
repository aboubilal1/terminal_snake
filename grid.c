#include "grid.h"
#include <stdio.h>

void init_grid(grid **g, int sizeX, int sizeY, char empty_cells_type) {
    *g = malloc(sizeof(grid));
    if(!(*g)) return;
    // printf("Grid initialized.\n");
    
    // initialize grid matrix and set default values to 0
    (*g)->sizeY = sizeY > 5 ? sizeY : 5;
    (*g)->matrix = malloc(sizeof(int*) * sizeY);
    
    (*g)->sizeX = sizeX >5 ? sizeX : 5;
    
    for(int i = 0; i < sizeY; i++) {
        (*g)->matrix[i] = malloc(sizeof(int) * sizeX);
        for(int j = 0; j < sizeX; j++) {
            if (!i && !j) (*g)->matrix[i][j] = 2; // snake head (0,0) cordenate
            else (*g)->matrix[i][j] = 0;
            // printf("%c ", (*g)->empty_cells_type);
            printf("0 ");
        }
        printf("\n");
    }
    
    (*g)->posX = 0;
    (*g)->posY = sizeY;
    
    (*g)->empty_cells_type = empty_cells_type;
    // (*g)->fp = fopen("file.txt", "w+");
    
    // printf("Grid size: %d x %d and it\'s cells_type is %c\n", (*g)->posX, (*g)->posY, (*g)->empty_cells_type);
}

// this function is call to initialize the printed grid or to reset it
void print_grid(grid *g) {
    // printf("printing. \n");
    for(int i = 0; i < g->sizeY; i++) {
        for(int j = 0; j < g->sizeX; j++) {
            printf("%c ", g->empty_cells_type);
        }
        printf("\n");
    }
}

void go_to_point(grid *g, int x, int y) {
    int dirx , diry;

    dirx = (x - g->posX) % 11;
    diry = (y - g->posY) % 11;
    g->posX = x + 1; // the + 1 is fro went print is get shifted to the right 
    g->posY = y;

    // to navigate through the printed grid
    if(diry < 0) { // to move up
        for (int i = 0; i < -diry; i++){
            printf("\033[A");
        }
    }else{ // to move down
        for (int i = 0; i < diry; i++){
            printf("\033[B");
        }
    }

    if(dirx < 0) { // to move left
        for (int i = 0; i < -dirx; i++){
            printf("\033[D\033[D");
        }
    }else{ // to move right
        for (int i = 0; i < dirx; i++){
            printf("\033[C\033[C");
        }
    }
}

void print_cell(char cells_type) {
    printf("%c ", cells_type);
}

void set_point_in_grid(grid *g, int x, int y, char cells_type) {        
    // if (g->fp == NULL) return;
    // fclose(g->fp);
    // g->fp = fopen("file.txt", "a+");
    // fprintf(g->fp, "point: (%d, %d)\t gridpos: (%d, %d)\t distance: (%d, %d)\t cells_type: %c\n\n", x, y, g->posX, g->posY, (x - g->posX) % 11, (y - g->posY) % 11, cells_type);
    if (cells_type == EMPTY){
        g->matrix[y][x] = 0;
    }else if (cells_type == BODY){
        g->matrix[y][x] = 1;
    }else if (cells_type == HEAD){
        g->matrix[y][x] = 2;
    }

    go_to_point(g, x, y);
    print_cell(cells_type);    
}