#include <stdio.h>

int main(){
    int operacion;
    float numero1, numero2, resultado;
    int error = 0;
    
    printf("Calculadora de Operaciones Basicas\n");
    printf("Por favor introduzca el primer numero: \n");
    scanf("%f", &numero1);
    printf("Por favor introduzca el segundo numero: \n");
    scanf("%f", &numero2);
    
    printf("Elige la Operacion a efectuar: (Responda solo con los numeros indicados)\n");
    printf("1. Suma \n");
    printf("2. Resta \n");
    printf("3. Multiplicacion \n");
    printf("4. Division \n");
    scanf("%d", &operacion);

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
        } 
        else {
            printf("\nError: No se puede dividir entre cero.\n");
            error = 1;
        }
        break;

    default:
        printf("\nOpcion no valida\n");
        error = 1;
        break;
    }

    if (error == 0){
        printf("El resultado es: %.4f", resultado);
    }
    
    return 0;
}
