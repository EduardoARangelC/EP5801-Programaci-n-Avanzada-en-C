#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arena_stack.h"

s_arena_stack* arena_stack_create(size_t item_size){

    /* Allocate memory for arena*/
        s_arena_stack* arena_ptr = malloc(sizeof(s_arena_stack) + sizeof(s_item_stack_header) + item_size);

            /* Check memory allocation was valid */
                if(arena_ptr == NULL){
                        exit(-1);
                            }

                                /* Populate structure for arena */
                                    arena_ptr->max_size = item_size;
                                        arena_ptr->offset = 0x00;
                                            arena_ptr->memory =  memset((void *)((uint8_t *)(arena_ptr) + sizeof(s_arena_stack)), 0x00, item_size);

                                                /* Return arena*/
                                                    return arena_ptr;
                                                    }

                                                    void* arena_stack_push(s_arena_stack* arena, size_t data_size, void* data){
                                                        /* Check arena exists before trying to add item */
                                                            if(arena == NULL){
                                                                    return NULL;
                                                                        }

                                                                            /* Get last item header for offset */
                                                                                s_item_stack_header last_item_header = {
                                                                                        .last_item = 0,
                                                                                                .size = 0
                                                                                                    };

                                                                                                        /* Check if its the first item */
                                                                                                            if(arena->offset != 0){
                                                                                                                    last_item_header = *((s_item_stack_header*) (((uint8_t*)(arena->memory)) + arena->offset - sizeof(s_item_stack_header)));
                                                                                                                        }

                                                                                                                            /* Check we have space in arena for allocation */
                                                                                                                                size_t remaining_space = arena->max_size - arena->offset - last_item_header.size;

                                                                                                                                    if(remaining_space < data_size + sizeof(s_item_stack_header)){
                                                                                                                                            return NULL;
                                                                                                                                                }


                                                                                                                                                    /* Create Header for data allocation */
                                                                                                                                                        s_item_stack_header item_header = {
                                                                                                                                                                .last_item = (void*) (((uint8_t*)(arena->memory)) + arena->offset),
                                                                                                                                                                        .size = data_size
                                                                                                                                                                            };
                                                                                                                                                                                
                                                                                                                                                                                    /* Copy Header to memory*/
                                                                                                                                                                                        memcpy((void*) ((((uint8_t*)(arena->memory)) + arena->offset + last_item_header.size)), &item_header, sizeof(s_item_stack_header));

                                                                                                                                                                                            /* Copy data to memory */
                                                                                                                                                                                                void* ptr = memcpy((void*) ((((uint8_t*)(arena->memory)) + arena->offset + last_item_header.size + sizeof(s_item_stack_header))), data, data_size);

                                                                                                                                                                                                    /* Update offset size */
                                                                                                                                                                                                        arena->offset += last_item_header.size + sizeof(s_item_stack_header);

                                                                                                                                                                                                            return ptr;
                                                                                                                                                                                                            }

                                                                                                                                                                                                            void* arena_stack_pop(s_arena_stack* arena, void* data){

                                                                                                                                                                                                                /* Check arena exists before trying to add item */
                                                                                                                                                                                                                    if(arena == NULL){
                                                                                                                                                                                                                            return NULL;
                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                    /* Check arena is not empty */
                                                                                                                                                                                                                                        if(arena->offset == 0){
                                                                                                                                                                                                                                                return NULL;
                                                                                                                                                                                                                                                    }

                                                                                                                                                                                                                                                        /* Get item header for size of item */
                                                                                                                                                                                                                                                            s_item_stack_header* item_header = (s_item_stack_header*) (((uint8_t*)(arena->memory)) + arena->offset - sizeof(s_item_stack_header));

                                                                                                                                                                                                                                                                /* Copy item to data pointer */
                                                                                                                                                                                                                                                                    void* ptr = memcpy(data, (void*) (((uint8_t*)(arena->memory))+ arena->offset), item_header->size);

                                                                                                                                                                                                                                                                        /* Get last item */
                                                                                                                                                                                                                                                                            if(arena->offset == sizeof(s_item_stack_header)){
                                                                                                                                                                                                                                                                                    arena->offset =0;
                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                            else{
                                                                                                                                                                                                                                                                                                    s_item_stack_header* last_item_header = (s_item_stack_header*) ((uint8_t*)item_header->last_item - sizeof(s_item_stack_header));

                                                                                                                                                                                                                                                                                                            arena->offset -= (last_item_header->size + sizeof(s_item_stack_header));
                                                                                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                                                                                    /* Set memory to zero for that header and data*/
                                                                                                                                                                                                                                                                                                                        memset((void*) item_header, 0x00, sizeof(s_item_stack_header) + item_header->size);

                                                                                                                                                                                                                                                                                                                            return ptr;
                                                                                                                                                                                                                                                                                                                            }

                                                                                                                                                                                                                                                                                                                            void arena_stack_free(s_arena_stack* arena){

                                                                                                                                                                                                                                                                                                                                /* Guard of freeing null pointer */
                                                                                                                                                                                                                                                                                                                                    if(arena->memory == NULL){
                                                                                                                                                                                                                                                                                                                                            return;
                                                                                                                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                                                                                                                    free(arena);
                                                                                                                                                                                                                                                                                                                                                    }