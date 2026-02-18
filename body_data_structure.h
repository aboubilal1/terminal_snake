#ifndef BODY_DATA_STRUCTURE_H
#define BODY_DATA_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include "body_part.h"

typedef struct body_data_structure{
    body_part *head;
    body_part *befor_tail;
    body_part *tail;
} body_data_structure;

void init_body_ds(body_data_structure **ds);
int empty_body_ds(body_data_structure *ds);
int one_element_ds(body_data_structure *ds);
void set_data(body_part *holder, body_part *new_data);

void body_ds_in_head(body_data_structure *ds, body_part data);
void body_ds_in_tail(body_data_structure *ds, body_part data);
void unbody_ds(body_data_structure *ds, body_part *data);
void set_before_tail(body_data_structure *ds);

void head_body_ds(body_data_structure *ds, body_part *data);
void before_tail_body_ds(body_data_structure *ds, body_part *data);
void tail_body_ds(body_data_structure *ds, body_part *data);

#endif