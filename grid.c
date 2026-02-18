#include "grid.h"
#include <stdio.h>

int init_grid(grid **g, int sizeX, int sizeY, char cells_character) {
    *g = malloc(sizeof(grid));
    if(!(*g)) return 0;
    (*g)->empty_cells_character = cells_character;
    // initialize grid matrix and set default values to 0
    (*g)->sizeY = sizeY > 5 ? sizeY : 5;
    (*g)->sizeX = sizeX >5 ? sizeX : 5;

    (*g)->matrix = malloc(sizeof(int*) * sizeY);
    
    
    for(int i = 0; i < sizeY; i++) {
        (*g)->matrix[i] = malloc(sizeof(int) * sizeX);
        for(int j = 0; j < sizeX; j++) {
            if (!i && !j) (*g)->matrix[i][j] = 2; // snake head (0,0) cordenate
            else (*g)->matrix[i][j] = 0;
            printf("%c ", (*g)->empty_cells_character); // initialize the grid with empty cells
            // printf("%d ", (*g)->matrix[i][j]); // initialize the grid with empty cells numiral value
        }
        printf("\n");
    }
    
    (*g)->cursor_position_X = 0;
    (*g)->cursor_position_Y = sizeY;
    
    (*g)->empty_cells_character = cells_character;
    // (*g)->fp = fopen("file.txt", "w+");
    
    return 1;
}

// this function is call to initialize the printed grid or to reset it
void print_grid(grid *g) {
    // printf("printing. \n");
    for(int i = 0; i < g->sizeY; i++) {
        for(int j = 0; j < g->sizeX; j++) {
            printf("%c ", g->empty_cells_character);
        }
        printf("\n");
    }
}

void go_to_point(grid *g, int x, int y) {
    int dirx , diry;

    dirx = (x - g->cursor_position_X) % 11;
    diry = (y - g->cursor_position_Y) % 11;
    g->cursor_position_X = x + 1; // the + 1 is fro went print is get shifted to the right 
    g->cursor_position_Y = y;

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

void print_cell(char cells_character) {
    printf("%c ", cells_character);
}

void set_point_in_grid(grid *g, int x, int y, char cells_character) {        
    // if (g->fp == NULL) return;
    // fclose(g->fp);
    // g->fp = fopen("file.txt", "a+");
    // fprintf(g->fp, "point: (%d, %d)\t gridpos: (%d, %d)\t distance: (%d, %d)\t cells_character: %c\n\n", x, y, g->cursor_position_X, g->cursor_position_Y, (x - g->cursor_position_X) % 11, (y - g->cursor_position_Y) % 11, cells_character);
    
    
    if (cells_character == EMPTY){
        g->matrix[y][x] = 0;
    }else if (cells_character == BODY){
        g->matrix[y][x] = 1;
    }else if (cells_character == HEAD){
        g->matrix[y][x] = 2;
    }
    
    go_to_point(g, x, y);
    print_cell(cells_character);    
}