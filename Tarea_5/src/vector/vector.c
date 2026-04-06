#include "vector.h"

#include "stdlib.h"

#include "string.h"

s_vector* vector_new(size_t item_size, e_vector_type type, size_t initial_size){

    /* Cant create null vectors */
    if(initial_size == 0){
        return NULL;
    }

    /* allocate memory for vector structure*/
    s_vector* vector = (s_vector*) malloc(sizeof(s_vector));

    /* In case we cannot allocate return null structure*/
    if(vector == NULL){
        return NULL;
    }

    /* Populate vector */
    vector->item_count = initial_size;
    vector->item_used = 0;
    vector->type = type;

    switch(type){

        /* Mask type to get acutal size of item for predefined types*/
        case u8:
        case u16:
        case u32:
        case u64:
        case f32:
        case f64:
            vector->item_size = 0x0f & type;
            break;

        /* Set variable item size for custom datatypes */
        default:
            vector->item_size = item_size;
            break;
    };

    /* Allocate initial memory for vector*/
    vector->memory = malloc(item_size * initial_size);

    /* Set data to zero en case it was shared before*/
    memset(vector->memory, 0x00, initial_size);

    /* If we cant allocate memory free vector structure and return null structure*/
    if(vector->memory == NULL){
        free(vector);
        return NULL;
    }

    return vector;
}

void vector_delete(s_vector* vector){

    /* We must check first that the vector is not null */
    if(vector != NULL){

        /* We free memory in case is allocated*/
        if(vector->memory != NULL){
            free(vector->memory);
        }

        /*Finally we free the vector*/
        free(vector);
    }
}

/* insert, get and delete */
bool vector_push(s_vector* vector, void* data){

    /* We guard against null data*/
    if(vector == NULL || vector->memory == NULL|| data == NULL){
        return false;
    }

    /* If there is no free space reallocate memory for the item using powers of two*/
    if(vector->item_count == vector->item_used){
        vector->item_count <<= 1;

        /* Reallocate memory, position of pointer could change*/
        vector->memory = realloc(vector->memory, vector->item_count);
    }

    /* Cast reference to free memory*/
    void* reference_ptr = (void*)((uint8_t*)vector->memory + (vector->item_used * (vector->item_size)));

    /* Copy the newly allocated data*/
    memcpy(reference_ptr,data,vector->item_size);
    vector->item_used++;

    return true;
}

bool vector_pop(s_vector* vector, void* storage){

    /* Guard against null memory positions*/
    if(vector == NULL || vector->memory == NULL || storage == NULL){
        return false;
    }

    /* Guard against no item in vector */
    if(vector->item_count == 0){
        return false;
    }

    /* Get reference of last item memory position*/
    void* reference_ptr = (void*)((uint8_t*)vector->memory + ((vector->item_used - 1) * (vector->item_size)));

    /* Copy Item*/
    memcpy(storage,reference_ptr,vector->item_size);

    /* zero the memory*/
    memset(reference_ptr,0x00, vector->item_size);

    vector->item_used--;

    return true;
}

bool vector_insert(s_vector* vector, void* data, size_t position){

    /* Guard against null memory positions*/
    if(vector == NULL || vector->memory == NULL || data == NULL){
        return false;
    }

    /* Guard against position larger than items used */
    if(position > vector->item_used){
        return NULL;
    }

    /* check if we have no more memory avaylable and reallocate */
    if(vector->item_count == vector->item_used){
        vector->item_count <<= 1;
        vector->memory = realloc(vector->memory, vector->item_count << 1);
    }

    /* Iterate through all indices from end of used data and shift them 1 item up to appen item*/
    for(size_t index = vector->item_used + 1; index > position; index--){ 
        void* destination_reference_ptr = (void*)((uint8_t*)vector->memory + (index * (vector->item_size)));
        void* copy_reference_ptr = (void*)((uint8_t*)vector->memory + ((index - 1) * (vector->item_size)));
        memcpy(destination_reference_ptr,copy_reference_ptr,vector->item_size);
        memset(copy_reference_ptr, 0x00, vector->item_size);
    }

    /* last item +1 reference */
    void* reference_ptr = (void*)((uint8_t*)vector->memory + (position * (vector->item_size)));

    /* Copy data*/
    memcpy(reference_ptr,data,vector->item_size);
    vector->item_used++;

    return true;
}

void* vector_at(s_vector* vector, size_t position){

    /* Guard against invalid memory */
    if(vector == NULL || vector->memory == NULL){
        return NULL;
    }
    
    /* Guard against unused items*/
    if(position >= vector->item_used){
        return NULL;
    }

    /* Return reference to item in memory*/
    return (void*) ((uint8_t*)vector->memory + (position * (vector->item_size)));
};


bool vector_erase(s_vector* vector, size_t position){

    /* Guard against invalid memory */
    if(vector == NULL || vector->memory == NULL){
        return false;
    }

    /* Guard against unused items*/
    if(position >= vector->item_used){
        return false;
    }

    /* We must clear the memory from n, and then copy n+1 into that area */
    for(size_t index = position; index < vector->item_used; index++){ 
        void* copy_reference_ptr = (void*)((uint8_t*)vector->memory + ((index + 1) * (vector->item_size)));
        void* destination_reference_ptr = (void*)((uint8_t*)vector->memory + (index * (vector->item_size)));
        memset(destination_reference_ptr, 0x00, vector->item_size);
        memcpy(destination_reference_ptr,copy_reference_ptr,vector->item_size);
    }

    vector->item_used--;

    return true;
}

/* Get actual vector size*/
size_t vector_size(s_vector* vector){

    if(vector == NULL || vector->memory == NULL) {
        return 0;
    }

    return vector->item_count;
}

/*Get if vector is empty*/
bool vector_empty(s_vector* vector){
    if(vector == NULL || vector->memory == NULL) {
        return 0;
    }

    return vector->item_used == 0;
}

/*  EXAMPLE OF USE:
    s_vector* vector_ptr = vector_new(sizeof(uint8_t));

    uint8_t test_data[] = {
        0xff, 0x00, 0x90, 0x01
    };

    vector_push(vector_ptr, &test_data[0]);      
    vector_push(vector_ptr, &test_data[1]);    
    vector_push(vector_ptr, &test_data[2]);    
    vector_push(vector_ptr, &test_data[3]);                

    vector_insert(vector_ptr, &test_data[0], 2);

    if(vector_empty(vector_ptr) == false){
        printf("Vector size: %lu\n",vector_size(vector_ptr));
    }

    vector_erase(vector_ptr, 1);            

    uint8_t test_ptr;
    vector_pop(vector_ptr, (void*) &test_ptr);   
    vector_pop(vector_ptr, (void*) &test_ptr);   
    vector_pop(vector_ptr, (void*) &test_ptr);   
    vector_pop(vector_ptr, (void*) &test_ptr);   

    
    vector_delete(vector_ptr);
*/