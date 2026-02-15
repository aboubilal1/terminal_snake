#include "body_ds.h"
#include <stdlib.h>

void init_body_ds(body_ds **ds){
    // printf("5 Initializing body_ds.\n");
    *ds = malloc(sizeof(body_ds));
    if (!(*ds)) return;
    // printf("5.1 Queue initialized.\n");
    (*ds)->head = NULL;
    (*ds)->befor_tail = NULL;
    (*ds)->tail = NULL;
}

int empty_body_ds(body_ds *ds){
    if (!ds){
        return 1;
    }
    return ds->head == NULL;
}
int one_element_ds(body_ds *ds){
    if (empty_body_ds(ds) || ds->head == ds->tail){
        return 1;
    }
    return 0;
}
int n_elements_in_ds(body_ds *ds, int n){
    if (n <= 0 || empty_body_ds(ds)) return 0;
    body_part *temp = ds->head;
    
    while (temp != NULL && --n){
        temp = temp->next;
    }
    if(n == 0) return 1;    
    else return 0;
}


void set_data(body_part *holder, body_part *new_data){
    holder->x = new_data->x;
    holder->y = new_data->y;
    // holder->type = new_data->type;
}

void body_ds_intail(body_ds *ds, body_part data){
    body_part *n = (body_part*)malloc(sizeof(body_part));
    if (!n) return;
    set_data(n, &data);
    n->next = NULL;

    if(empty_body_ds(ds)){
        ds->head = n;
        ds->tail = n;
    }else{
        ds->tail->next = n;
        ds->tail = n;
    }
}

void body_ds_inhead(body_ds *ds, body_part data){
    body_part *n = (body_part*)malloc(sizeof(body_part));
    if (!n) return;
    set_data(n, &data);
    n->next = NULL;

    if(empty_body_ds(ds)){
        printf("in the add in haed empty\n");
        ds->head = n;
        ds->tail = n;
    }else{
        printf("in the add in haed non-empty\n");
        n->next = ds->head;
        ds->head = n;
    }
    n = NULL;
    free(n);
}
void set_before_tail(body_ds *ds){
    if (!n_elements_in_ds(ds, 3)) {
        ds->befor_tail = ds->head;
        printf("add body part2.2.1, %p\t", ds->head);
        printf("add body part2.2.1, %p\t", ds->tail);
        printf("add body part2.2.1, %p\n", ds->befor_tail);
    }
    else {
        ds->befor_tail = ds->befor_tail->next;
        printf("add body part2.2.2, %p\t", ds->head);
        printf("add body part2.2.2, %p\t", ds->tail);
        printf("add body part2.2.2, %p\n", ds->befor_tail);
    }
    

}

void unbody_ds(body_ds *ds, body_part *data){
    if (empty_body_ds(ds)){
        return;
    }
    set_data(data, ds->head);
    ds->head = ds->head->next;
}


void head_body_ds(body_ds *ds, body_part *data){
    if (empty_body_ds(ds)){
        data->x = -1; data->y = -1;
        data->next = NULL;
        return;
    }
    set_data(data, ds->head);
}

void before_tail_body_ds(body_ds *ds, body_part *data){
    if (empty_body_ds(ds)){
        data->x = -1; data->y = -1;
        data->next = NULL;
        return;
    }
    set_data(data, ds->befor_tail);
}

void tail_body_ds(body_ds *ds, body_part *data){
    if (empty_body_ds(ds)){
        data->x = -1; data->y = -1;
        data->next = NULL;
        return;
    }
    set_data(data, ds->tail);
}
