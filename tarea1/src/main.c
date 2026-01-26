#include <stdio.h>
#include "calculador.h"

int main() {
    float num1, num2, resultado;
    int op, error;
    int continuar = 1;
    
    printf("\nCalculadora de Operaciones Basicas\n");
    while (continuar == 1) {

    printf("Por favor introduzca el primer numero: ");
    if (scanf("%f", &num1) != 1) {
        printf("Entrada invalida\n");
        break;
    }

    printf("Por favor introduzca el segundo numero: ");
    if (scanf("%f", &num2) != 1) {
        printf("Entrada invalida\n");
        break;
    }

    printf("Elige la Operacion a efectuar:\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicacion\n");
    printf("4. Division\n");
    scanf("%d", &op);

    resultado = calcular(num1, num2, op, &error);

    if (error == 0) {
        printf("El resultado es: %.4f\n", resultado);
    }

    printf("\nDesea realizar otra operacion? (1 = si, 0 = no): ");
    if (scanf("%d", &continuar) != 1) {
        printf("Entrada invalida\n");
        break;
    }
}

return 0;
}



