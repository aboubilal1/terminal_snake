#include "snake.h"
#include <stdio.h>
#include <stdlib.h>


void init_snake(snake_head **head){
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
    (*head) = malloc(sizeof(snake_head));
    if (!(*head)) return;
    
    (*head)->right = RIGHT;
    (*head)->left = LEFT;
    (*head)->up = UP;
    (*head)->down = DOWN;
    
    
    (*head)->speed = 20;
    
    (*head)->dirx = 1;
    (*head)->diry = 0;
    
    (*head)->x = 0;
    (*head)->y = 0;
    
    
    // (*head)->replaced = malloc(3 * sizeof(body_part));
    
    // init_grid(&(*head)->grid, 10, 10, EMPTY);

    init_queue(&(*head)->direction);
    queue_in((*head)->direction, 3);
    
    (*head)->grid = malloc(sizeof(grid));
    init_body_ds(&(*head)->body_ds);
    
    add_body_part(*head);
    add_body_part(*head);
    add_body_part(*head);

}


// to add here
void add_body_part(snake_head *head){    
    // add a body part at the head of the snake data structure
    // that get the same position as the last
    body_part data ;
    if (empty_body_ds(head->body_ds)) {
        data = (body_part) {head->x, head->y, NULL}; // for the head initialization 
    }else{
        head_body_ds(head->body_ds, &data);
    }
    
    body_ds_inhead(head->body_ds, data);
    printf("add body part2.1 x: %d y: %d\t", data.x, data.y);
    set_before_tail(head->body_ds);
}


void set_direction(snake_head **head, int dt){
    // (*head)->frames_to_move += dt;
    int dir;
    head_queue((*head)->direction, &dir);
    if((*head)->speed <= 0) return;
    
    // set_cordinate the direction of the snake
    if ((*head)->dirx == 0 && (dir == (*head)->left || dir == (*head)->right)) {
        (*head)->diry = 0;
        if(dir == (*head)->left){
            (*head)->dirx = -1;
        }else{
            (*head)->dirx = 1;
        }
    }else if ((*head)->diry == 0 && (dir == (*head)->up || dir == (*head)->down)) {
        (*head)->dirx = 0;
        if(dir == (*head)->up){
            (*head)->diry = -1;
        }else{
            (*head)->diry = 1;
        }
    }

    move_it(head, dt);
}

int calculate_new_position(snake_head *head, double *new_x, double *new_y, int dt){
    if (head == NULL) return 0;
    int dirx  = head->dirx , diry = head->diry;
    int speed = head->speed;

    // calculate the new position
    double deltaX = ((double)(dirx * speed)) / (dt);
    double deltaY = ((double)(diry * speed)) / (dt);

    *new_x = head->x + deltaX;
    *new_y = head->y + deltaY;
    return 1;
}

void move_it(snake_head **head, int dt){
    
    double new_x = 0.0, new_y = 0.0;
    if(!calculate_new_position(*head, &new_x, &new_y, dt))return;
    printf("move it x: %f y: %f\n", new_x, new_y);
    // check if the new position is deffrent from the old one
    if((int)new_x != (int)(*head)->x || (int)new_y != (int)(*head)->y){
        // check if there is only one direction in the queue
        // if so stay in the same direction
        // else unqueue the head
        if(!one_element_queue((*head)->direction)){
            int *dummy = malloc(sizeof(int));
            unqueue((*head)->direction, dummy);
            free(dummy);
        }
        // remove the head and add a new part to the end with the new position
        body_part *new_part = malloc(sizeof(body_part));
        unbody_ds((*head)->body_ds, new_part);
        set_cordinate(new_part, (int)new_x, (int)new_y);
        body_ds_intail((*head)->body_ds, *new_part);
        printf("after ");
        free(new_part);
        // add the new parts to the replaced part
        // add_replace_part(head, get_x((*head)->body), get_y((*head)->body), BODY, 1);
        // add_replace_part(head, normalize((int)new_x), normalize((int)new_y), HEAD, 2);
        
        // move the snake

        // ############# the problem is here ###################
        // display_moves(*head, (*head)->grid);

    }

    (*head)->x = new_x;
    (*head)->y = new_y;
}

/*handle the replaced parts from adding to sorting 
    the default order is
    0 - tail
    1 - body
    2 - head
    then sorting them acording to the (x,y) of part
*/
/*

void add_replace_part(snake_head **head, int x, int y, char type, int pos){
    // printf("the placed parts: %p in (%d,%d) %c\n",(*head)->replaced, x, y, type);
    ((*head)->replaced + pos)->x = x;
    ((*head)->replaced + pos)->y = y;
    // ((*head)->replaced + pos)->type = type;
}

void swaper(body_part *a, body_part *b){
    body_part temp = *a;
    *a = *b;
    *b = temp;
}

void sort_the_replaced(snake_head **head){    
    // printf("1- the replaced parts: %p\n",(*head)->replaced);
    // for(body_part *ptr = (*head)->replaced; ptr < (*head)->replaced+3; ptr++){
    //     printf("(%d,%d) %c\n", ptr->x, ptr->y, ptr->type);
    // }


    for(int i=0; i<3; i++){
        for(int j=i+1; j<3; j++){
            // sort the replaced parts by the y then the x from large to small
            if((*head)->replaced[i].y > (*head)->replaced[j].y){

                swaper((*head)->replaced+i, (*head)->replaced+j);

            }else if((*head)->replaced[i].y == (*head)->replaced[j].y){
                if((*head)->replaced[i].x > (*head)->replaced[j].x){

                    swaper((*head)->replaced+i, (*head)->replaced+j);

                }
            }
        }
    }

    // printf("2- the replaced parts: %p\n",(*head)->replaced);
    // for(body_part *ptr = (*head)->replaced; ptr < (*head)->replaced+3; ptr++){
    //     printf("(%d,%d) %c\n", ptr->x, ptr->y, ptr->type);
    // }

}
*/



// helper functions

int get_x(body_part *s){
    return (s->x)%10;
}
int get_y(body_part *s){
    return (s->y)%10;
}
void set_cordinate(body_part *s, int x, int y){
    s->x = (x+10)%10;
    s->y = (y+10)%10;
}
int normalize(int x){
    return (x+10)%10;
}
void direction(snake_head **head, int *dir){
    if(!(*dir))return;
    queue_in((*head)->direction, *dir);
    dir = 0;
}
void display_moves(snake_head *s, grid *grid){
    body_part data;
    
    if (!empty_body_ds(s->body_ds)){
        head_body_ds(s->body_ds, &data);
        set_point_in_grid(grid, data.x, data.y, EMPTY);
        
        if (!one_element_ds(s->body_ds)){
            before_tail_body_ds(s->body_ds, &data);
            set_point_in_grid(grid, data.x, data.y, BODY);
        }
        
        tail_body_ds(s->body_ds, &data);
        set_point_in_grid(grid, data.x, data.y, HEAD);
    }
}
void progamma_exit(snake_head **s){
    set_point_in_grid((*s)->grid, (*s)->grid->posX, (*s)->grid->sizeY, ' ');
    free((*s));
}