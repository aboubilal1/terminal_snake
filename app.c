#include "snake.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <sys/time.h>

// void enableANSI() {
//     HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//     DWORD mode;
//     GetConsoleMode(h, &mode);
//     SetConsoleMode(h, mode | 0x4);  // ENABLE_VIRTUAL_TERMINAL_PROCESSING
// }
double getCurrentTime();


int next_frame(double *last_move, int *dt, int fps);

int setit(int dir);

void quit(snake_head *s, double *last_move);


int main(void) {
    // enableANSI();
    // printf("starting");
    
    snake_head *s;
    init_snake(&s);
    
    double start = getCurrentTime();
    double *last_move = malloc(sizeof(double));
    *last_move = start;
    
    int dir;
    int fps = 1000/30, dt = fps;
    while(1){
        if (next_frame(last_move, &dt, fps)){
            Sleep(100);
            if (kbhit()) {
                printf("const char *\n");

                dir = getch();  // Real-time input
                // for test the grid manually
                // if(dir == 'a') go_to_point(s->grid, s->grid->posX - 1, s->grid->posY);
                // if(dir == 'd') go_to_point(s->grid, s->grid->posX + 1, s->grid->posY);
                // if(dir == 'w') go_to_point(s->grid, s->grid->posX, s->grid->posY - 1);
                // if(dir == 's') go_to_point(s->grid, s->grid->posX, s->grid->posY + 1);
                if(dir == 32) add_body_part(s);
                
                // for moving the snake
                if(dir == 'a') dir = LEFT;
                if(dir == 'd') dir = RIGHT;
                if(dir == 'w') dir = UP;
                if(dir == 's') dir = DOWN;

                if(dir == 27) {
                    quit(s, last_move);
                    break;
                }// ESC to quit
                direction(&s, &dir);
            }
            set_direction(&s, dt);
        }

    
    //     // printf("snake head in x = %d; y = %d\n", s->body->x, s->body->y);
    }    
    // set_point_in_grid(s->grid, s->body->x, s->body->y, '@');
    // set_point_in_grid(s->grid, 4, 4, 'O');
    return 0;
}


double getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0) * 1000;
}

int next_frame(double *last_move, int *dt, int fps){
    double now = getCurrentTime();
    *dt = (int) (now - *last_move);
    if (*dt >= fps){
        // printf("dt: %d, now: %f, last_move: %f\n", dt, now, *last_move);
        *last_move = now;
        return 1;
    }
    return 0;
}

int setit(int dir){
    if (dir == 1) return LEFT;
    if (dir == 2) return RIGHT;
    if (dir == 3) return UP;
    if (dir == 4) return DOWN;
    return 1;
}

void quit(snake_head *s, double *last_move){
    progamma_exit(&s);
    free(s);
    free(last_move);
    // fclose(s->grid->fp);
}