#include "vector_math.h"

#include "../asm/avx/avx.h"

static void vector_add_u8(s_vector* vector_a, s_vector* vector_b, s_vector* result){
    for(size_t index =0 ; index < vector_a->item_used; index++){
        *((uint8_t *)result->memory + index) = *((uint8_t*)vector_a->memory + index) + *((uint8_t*)vector_b->memory + index) ;
    }   
}

static void vector_add_u8_avx(s_vector* vector_a, s_vector* vector_b, s_vector* result, size_t cycle_repetitions){
    for(size_t index =0 ; index < cycle_repetitions; index++){
        size_t offset = index * 32;
        avx_uint8_t(((uint8_t *)vector_a->memory + offset), ((uint8_t *)vector_b->memory + offset), ((uint8_t *)result->memory + offset));
    }
}

static void vector_add_u16(s_vector* vector_a, s_vector* vector_b, s_vector* result){
    for(size_t index =0 ; index < vector_a->item_used; index++){
        *((uint16_t *)result->memory + index) = *((uint16_t*)vector_a->memory + index) + *((uint16_t*)vector_b->memory + index) ;
    }   
}

static void vector_add_u16_avx(s_vector* vector_a, s_vector* vector_b, s_vector* result, size_t cycle_repetitions){
    for(size_t index =0 ; index < cycle_repetitions; index++){
        size_t offset = index * 16;
        avx_uint16_t(((uint16_t *)vector_a->memory + offset), ((uint16_t *)vector_b->memory + offset), ((uint16_t *)result->memory + offset));
    }
}

static void vector_add_u32(s_vector* vector_a, s_vector* vector_b, s_vector* result){
    for(size_t index =0 ; index < vector_a->item_used; index++){
        *((uint32_t *)result->memory + index) = *((uint32_t*)vector_a->memory + index) + *((uint32_t*)vector_b->memory + index) ;
    }   
}

static void vector_add_u32_avx(s_vector* vector_a, s_vector* vector_b, s_vector* result, size_t cycle_repetitions){
    for(size_t index =0 ; index < cycle_repetitions; index++){
        size_t offset = index * 8;
        avx_uint32_t(((uint32_t *)vector_a->memory + offset), ((uint32_t *)vector_b->memory + offset), ((uint32_t *)result->memory + offset));
    }
}

static void vector_add_u64(s_vector* vector_a, s_vector* vector_b, s_vector* result){
    for(size_t index =0 ; index < vector_a->item_used; index++){
        *((uint64_t *)result->memory + index) = *((uint64_t*)vector_a->memory + index) + *((uint64_t*)vector_b->memory + index) ;
    }   
}

static void vector_add_u64_avx(s_vector* vector_a, s_vector* vector_b, s_vector* result, size_t cycle_repetitions){
    for(size_t index =0 ; index < cycle_repetitions; index++){
        size_t offset = index * 4;
        avx_uint64_t(((uint64_t *)vector_a->memory + offset), ((uint64_t *)vector_b->memory + offset), ((uint64_t *)result->memory + offset));
    }
}

static void vector_add_f32(s_vector* vector_a, s_vector* vector_b, s_vector* result){
    for(size_t index =0 ; index < vector_a->item_used; index++){
        *((uint32_t *)result->memory + index) = *((uint32_t*)vector_a->memory + index) + *((uint32_t*)vector_b->memory + index) ;
    }   
}

static void vector_add_f32_avx(s_vector* vector_a, s_vector* vector_b, s_vector* result, size_t cycle_repetitions){
    for(size_t index =0 ; index < cycle_repetitions; index++){
        size_t offset = index * 8;
        avx_float32_t(((float *)vector_a->memory + offset), ((float *)vector_b->memory + offset), ((float *)result->memory + offset));
    }
}

static void vector_add_f64(s_vector* vector_a, s_vector* vector_b, s_vector* result){
    for(size_t index =0 ; index < vector_a->item_used; index++){
        *((uint64_t *)result->memory + index) = *((uint64_t*)vector_a->memory + index) + *((uint64_t*)vector_b->memory + index) ;
    }   
}

void vector_add(s_vector* vector_a, s_vector* vector_b, s_vector* result){

    /* We need to ensure both vector has the same size */
    if(vector_a->item_count != vector_b->item_count ||  vector_a->item_count > result->item_count){
        return;
    }

    /* We need to ensure both vector has the same data size */
    if(vector_a->type != vector_b->type){
        return;
    }

    size_t cycle_repetitions;
    switch (vector_a->type){
        case u8:
            cycle_repetitions = vector_a->item_count / 32;
            if(cycle_repetitions > 0){
                vector_add_u8_avx(vector_a, vector_b, result, cycle_repetitions);
            }
            else{
                vector_add_u8(vector_a, vector_b, result);
            }
            result->item_used = vector_a->item_used >= vector_b->item_used ? vector_a->item_used : vector_b->item_used;
            break;
        
        case u16:
            cycle_repetitions = vector_a->item_count / 16;
            if(cycle_repetitions > 0){
                vector_add_u16_avx(vector_a, vector_b, result, cycle_repetitions);
            }
            else{
                vector_add_u16(vector_a, vector_b, result);
            }
            result->item_used = vector_a->item_used >= vector_b->item_used ? vector_a->item_used : vector_b->item_used;
            break;

        case u32:
            cycle_repetitions = vector_a->item_count / 8;
            if(cycle_repetitions > 0){
                vector_add_u32_avx(vector_a, vector_b, result, cycle_repetitions);
            }
            else{
                vector_add_u32(vector_a, vector_b, result);
            }
            result->item_used = vector_a->item_used >= vector_b->item_used ? vector_a->item_used : vector_b->item_used;
            break;

        case u64:
            cycle_repetitions = vector_a->item_count / 4;
            if(cycle_repetitions > 0){
                vector_add_u64_avx(vector_a, vector_b, result, cycle_repetitions);
            }
            else{
                vector_add_u64(vector_a, vector_b, result);
            }
            result->item_used = vector_a->item_used >= vector_b->item_used ? vector_a->item_used : vector_b->item_used;
            break;

        case f32:
            cycle_repetitions = vector_a->item_count / 8;
            if(cycle_repetitions > 0){
                vector_add_f32_avx(vector_a, vector_b, result, cycle_repetitions);
            }
            else{
                vector_add_f32(vector_a, vector_b, result);
            }
            result->item_used = vector_a->item_used >= vector_b->item_used ? vector_a->item_used : vector_b->item_used;
            break;

        case f64:
            vector_add_f64(vector_a, vector_b, result);
            result->item_used = vector_a->item_used >= vector_b->item_used ? vector_a->item_used : vector_b->item_used;
            break;

        /* Don't do arithmethic with unkown types*/
        default:
            return;
    }

}