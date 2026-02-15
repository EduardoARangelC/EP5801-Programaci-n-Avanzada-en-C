#include <stdio.h>
#include "gest.h"

// Puntero global para almacenar los datos del sensor de gestos
s_gestos * ptr_gestos;

// Función para imprimir los datos del sensor de gestos
void print_gestos(){
    if (ptr_gestos->tap) {
        printf("Tap\n");
    } else if (ptr_gestos->double_tap) {
        printf("Doble Tap\n");
    } else if (ptr_gestos->haptic_press) {
        printf("Presion haptica\n");
    } else {
        printf("Ningun gesto detectado\n");
    }
}

// Función para procesar los datos del sensor de gestos
print_sensor gestos(uint8_t * data){
    // Asignar el puntero global a la dirección de los datos del sensor
    ptr_gestos = (s_gestos *) data;

    return print_gestos;
}