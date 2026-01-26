#include <stdio.h>
#include "calculador.h"

float calcular(float numero1, float numero2, int operacion, int *error) {
    float resultado = 0;
    *error = 0;

    switch (operacion)
    {
    case 1:
        resultado = numero1 + numero2;
        break;

    case 2:
        resultado = numero1 - numero2;
        break;

    case 3:
        resultado = numero1 * numero2;
        break;

    case 4:
        if (numero2 != 0) {
            resultado = numero1 / numero2;
        } else {
            printf("\nError: No se puede dividir entre cero.\n");
            *error = 1;
        }
        break;

    default:
        printf("\nOpcion no valida\n");
        *error = 1;
        break;
    }

    return resultado;
}

