#include "snake.h"
#include <stdio.h>
#include <stdlib.h>


void init_snake(snake_head **snake){
    /* initialize the snake with default values
        { 
          left, right, up, down
          speed = 10
          dirx = 1, diry = 0  
        x and y are used to indicate the start posintion 
          x = 10, y = 10
        }
        and add 3 body parts at the start (0,0)
    */ 
    (*snake) = malloc(sizeof(snake_head));
    if (!(*snake)) return;
    
    (*snake)->right = RIGHT;
    (*snake)->left = LEFT;
    (*snake)->up = UP;
    (*snake)->down = DOWN;
    
    
    (*snake)->speed = 20;
    
    (*snake)->dirx = 1;
    (*snake)->diry = 0;
    
    (*snake)->x = 0;
    (*snake)->y = 0;
    
        
    init_grid(&(*snake)->grid, 10, 10, EMPTY);


    init_queue(&(*snake)->direction_queue);
    queue_in((*snake)->direction_queue, 3);
    
    init_body_ds(&(*snake)->body_data_structure);
    
    add_body_part(*snake);
    add_body_part(*snake);
    add_body_part(*snake);

}


// to add here
void add_body_part(snake_head *snake){    
    // add a body part at the snake of the snake data structure
    // that get the same position as the last
    body_part data ;
    if (empty_body_ds(snake->body_data_structure)) {
        data = (body_part) {snake->x, snake->y, NULL}; // for the snake initialization 
    }else{
        head_body_ds(snake->body_data_structure, &data);
    }
    body_ds_in_head(snake->body_data_structure, data);
    // printf("add body part2.1 x: %d y: %d\t", data.x, data.y);

    // printf("%p add body part1\n", snake->body_data_structure->head);
    // printf("%p add body part1\n", snake->body_data_structure->befor_tail);
    // printf("%p add body part1\n", snake->body_data_structure->tail);
}


void set_direction(snake_head **snake, int dalta_time){
    // (*snake)->frames_to_move += dalta_time;
    int direction;
    head_queue((*snake)->direction_queue, &direction);
    if((*snake)->speed <= 0) return;
    
    // set_cordinate the direction of the snake
    if ((*snake)->dirx == 0 && (direction == (*snake)->left || direction == (*snake)->right)) {
        (*snake)->diry = 0;
        if(direction == (*snake)->left){
            (*snake)->dirx = -1;
        }else{
            (*snake)->dirx = 1;
        }
    }else if ((*snake)->diry == 0 && (direction == (*snake)->up || direction == (*snake)->down)) {
        (*snake)->dirx = 0;
        if(direction == (*snake)->up){
            (*snake)->diry = -1;
        }else{
            (*snake)->diry = 1;
        }
    }

    move_it(snake, dalta_time);
}

int calculate_new_position(snake_head *snake, double *new_x, double *new_y, int dalta_time){
    if (snake == NULL) return 0;
    int dirx  = snake->dirx , diry = snake->diry;
    int speed = snake->speed;

    // calculate the new position
    double deltaX = ((double)(dirx * speed)) / (dalta_time);
    double deltaY = ((double)(diry * speed)) / (dalta_time);

    *new_x = snake->x + deltaX;
    *new_y = snake->y + deltaY;
    return 1;
}

void move_it(snake_head **snake, int dalta_time){
    
    double new_x = 0.0, new_y = 0.0;
    if(!calculate_new_position(*snake, &new_x, &new_y, dalta_time))return;
    // printf("move it x: %f y: %f\n", new_x, new_y);
    // check if the new position is deffrent from the old one
    if((int)new_x != (int)(*snake)->x || (int)new_y != (int)(*snake)->y){
        // check if there is only one direction in the queue
        // if so stay in the same direction
        // else unqueue from the snake direction queue
        if(!one_element_queue((*snake)->direction_queue)){
            int *dummy = malloc(sizeof(int));
            int *dummy_test = malloc(sizeof(int));
            unqueue((*snake)->direction_queue, dummy);
            head_queue((*snake)->direction_queue, dummy_test);
            while(*dummy == *dummy_test && !one_element_queue((*snake)->direction_queue)){
                unqueue((*snake)->direction_queue, dummy_test); // to remove the repeated move at the same sequence
            }
            free(dummy);
            free(dummy_test);
        }
        // remove the snake and add a new part to the end with the new position
        body_part *new_part = malloc(sizeof(body_part));
        
        set_cordinate(new_part, (int)new_x, (int)new_y);
        body_ds_in_tail((*snake)->body_data_structure, *new_part);
        // move the snake
        display_moves(*snake);
        
        unbody_ds((*snake)->body_data_structure, new_part);
        free(new_part);
    }

    (*snake)->x = new_x;
    (*snake)->y = new_y;
}

/*handle the replaced parts from adding to sorting 
    the default order is
    0 - tail
    1 - body
    2 - snake
    then sorting them acording to the (x,y) of part
*/
/*

void add_replace_part(snake_head **snake, int x, int y, char type, int pos){
    // printf("the placed parts: %p in (%d,%d) %c\n",(*snake)->replaced, x, y, type);
    ((*snake)->replaced + pos)->x = x;
    ((*snake)->replaced + pos)->y = y;
    // ((*snake)->replaced + pos)->type = type;
}

void swaper(body_part *a, body_part *b){
    body_part temp = *a;
    *a = *b;
    *b = temp;
}

void sort_the_replaced(snake_head **snake){    
    // printf("1- the replaced parts: %p\n",(*snake)->replaced);
    // for(body_part *ptr = (*snake)->replaced; ptr < (*snake)->replaced+3; ptr++){
    //     printf("(%d,%d) %c\n", ptr->x, ptr->y, ptr->type);
    // }


    for(int i=0; i<3; i++){
        for(int j=i+1; j<3; j++){
            // sort the replaced parts by the y then the x from large to small
            if((*snake)->replaced[i].y > (*snake)->replaced[j].y){

                swaper((*snake)->replaced+i, (*snake)->replaced+j);

            }else if((*snake)->replaced[i].y == (*snake)->replaced[j].y){
                if((*snake)->replaced[i].x > (*snake)->replaced[j].x){

                    swaper((*snake)->replaced+i, (*snake)->replaced+j);

                }
            }
        }
    }

    // printf("2- the replaced parts: %p\n",(*snake)->replaced);
    // for(body_part *ptr = (*snake)->replaced; ptr < (*snake)->replaced+3; ptr++){
    //     printf("(%d,%d) %c\n", ptr->x, ptr->y, ptr->type);
    // }

}
*/



// helper functions

int get_x(body_part *snake_body){
    return (snake_body->x)%10;
}
int get_y(body_part *snake_body){
    return (snake_body->y)%10;
}
void set_cordinate(body_part *snake_body, int x, int y){
    snake_body->x = (x+10)%10;
    snake_body->y = (y+10)%10;
}
int normalize(int x){
    return (x+10)%10;
}
void direction(snake_head **snake, int *direction){
    if(!(*direction))return;
    queue_in((*snake)->direction_queue, *direction);
    direction = 0;
}
void display_moves(snake_head *snake){
    body_part data;
    grid *grid = snake->grid;
    // printf("setting in grid gridpos.x = %d, gridpos.y = %dhgjfjfhg\n", grid->cursor_position_X, grid->cursor_position_Y );
    if (!empty_body_ds(snake->body_data_structure)){
        head_body_ds(snake->body_data_structure, &data);
        set_point_in_grid(grid, data.x, data.y, EMPTY);
        
        if (!one_element_ds(snake->body_data_structure)){
            before_tail_body_ds(snake->body_data_structure, &data);
            set_point_in_grid(grid, data.x, data.y, BODY);
        }
        
        tail_body_ds(snake->body_data_structure, &data);
        set_point_in_grid(grid, data.x, data.y, HEAD);
    }
}
void progamma_exit(snake_head **snake){
    set_point_in_grid((*snake)->grid, (*snake)->grid->cursor_position_X, (*snake)->grid->sizeY, ' ');
    free((*snake));
}