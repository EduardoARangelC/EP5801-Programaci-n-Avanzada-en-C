// Tarea #2 EP5801
// Eduardo Rangel Carnet: 20-10533
// Pagina consultada: https://www.geeksforgeeks.org/c/fgets-function-in-c/

// Programa que imprime un string usando assembly
#include <stdio.h>
#include <string.h>

void imprimir(char* mensaje, long caracteres);

int main() {
    long caracteres;
    char buffer[256]; // Reserva espacio para un string de 256 caracteres 

    printf("Introduce un string: ");
    fgets(buffer, sizeof(buffer), stdin);

    caracteres = strlen(buffer);

    imprimir(buffer, caracteres);   // Llama al .asm para imprimir el string
    return 0;
}