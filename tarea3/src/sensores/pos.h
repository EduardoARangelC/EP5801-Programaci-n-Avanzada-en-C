#ifndef POS_H
#define POS_H

#include <stdint.h>
#include "sensores.h" 

// Estructura del sensor para almacenar la posición
typedef struct S_POSICION {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t pos_z;
} s_posicion;

print_sensor posicion(uint8_t * data);

#endif