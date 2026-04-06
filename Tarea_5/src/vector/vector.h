#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdbool.h>

#include "vector_common.h"

/* Creation and deletion */
s_vector* vector_new(size_t item_size, e_vector_type type, size_t initial_size); //Create new vector for data type
void vector_delete(s_vector* vector);   //Delete vector

/* insert, get and delete */
bool vector_push(s_vector* vector, void* data);                     //Push to back of the vector
bool vector_pop(s_vector* vector, void* storage);                               //Pop from the back of the vector
bool vector_insert(s_vector* vector, void* data, size_t position);  //Insert at desired position
void* vector_at(s_vector* vector, size_t position);                 //Get reference at desired position
bool vector_erase(s_vector* vector, size_t position);               //Erase at desired position and shift

/* Extra operations */
size_t vector_size(s_vector* vector);   //Get vector items in use
bool vector_empty(s_vector* vector);    //Get if vector is beign used

#endif