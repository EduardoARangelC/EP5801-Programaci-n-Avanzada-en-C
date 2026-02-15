#ifndef GEST_H
#define GEST_H

#include <stdint.h>
#include "sensores.h"

// Estructura para las funciones del sensor de gestos
typedef struct S_GESTOS {
    uint8_t tap: 1; // 1 Bit para indicar si se detectó un tap
    uint8_t double_tap: 1;
    uint8_t haptic_press: 1;
    uint8_t reserved: 5; // Bits reservados para llegar a completar un byte
} s_gestos;

// Función para procesar los datos del sensor de gestos
print_sensor gestos(uint8_t * data);

#endif