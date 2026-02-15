#include <stdio.h>
#include "pos.h"

// Variable global para almacenar la posición actual
s_posicion * ptr_posicion;

// Función para imprimir la posición actual
void print_pos(){
    printf("x: %u, y: %u, z: %u \n", ptr_posicion->pos_x, ptr_posicion->pos_y, ptr_posicion->pos_z);
}

print_sensor posicion(uint8_t * data){
    ptr_posicion = (s_posicion *) data;

    return print_pos;
}