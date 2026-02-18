#ifndef BODY_DS_H
#define BODY_DS_H

#include <stdio.h>
#include <stdlib.h>
#include "body_part.h"

typedef struct body_ds{
    body_part *head;
    body_part *befor_tail;
    body_part *tail;
} body_ds;

void init_body_ds(body_ds **ds);
int empty_body_ds(body_ds *ds);
int one_element_ds(body_ds *ds);
void set_data(body_part *holder, body_part *new_data);

void body_ds_inhead(body_ds *ds, body_part data);
void body_ds_intail(body_ds *ds, body_part data);
void unbody_ds(body_ds *ds, body_part *data);
void set_before_tail(body_ds *ds);

void head_body_ds(body_ds *ds, body_part *data);
void before_tail_body_ds(body_ds *ds, body_part *data);
void tail_body_ds(body_ds *ds, body_part *data);

#endif