#include <stdio.h>
#include <stddef.h>
#include "sensores/sensores.h"
#include "sensores/gest.h"
#include "sensores/pos.h"

int main() {
    
    // Prueba para el sensor de gestos
    /* uint8_t data_sensor[] = {
        0xB0, //ID del sensor
        0x07, // Accion del sensor
    }; */

    // Prueba para el sensor de posicion
    uint8_t data_sensor[] = {
        0xA0, //ID del sensor
        0x12, 0x00,  // X: 18
        0x06, 0x00,  // Y: 06
        0xCB, 0x00   // Z: 203 
    };

    print_sensor print_data;

    // Identificar el sensor y usar la función correspondiente para imprimir los datos
    switch (data_sensor[0]){
        case pos_id:
            print_data = posicion(data_sensor + 1);
            break;
        case gest_id:
            print_data = gestos(data_sensor + 1);
            break;
        default:
            printf("Sensor no reconocido\n");
            return -1;
    }

    if (print_data != NULL) {
        print_data();
    }

    return 0;
}
