#include <stdio.h>
#include <string.h>
#include <math.h>
#include "./arena/arena_stack.h"
#include "./calculador.h"

#define BUFFER_SIZE 256
// Espacio de memoria
static char buffer_estatico[BUFFER_SIZE];

int main() {
    char continuar = 'n';

    do {
        printf("\nCalculadora RPN (Operaciones permitidas: +, -, *, /)\nIngrese su expresion: ");
        
        int i = 0;
        int c;
        // Limpiar buffer estático antes de usar
        memset(buffer_estatico, 0, BUFFER_SIZE);

        while ((c = getchar()) != '\n' && c != EOF && i < BUFFER_SIZE - 1) {
            buffer_estatico[i++] = (char)c;
        }
        buffer_estatico[i] = '\0';

        if (strlen(buffer_estatico) > 0) {
            size_t lon = strlen(buffer_estatico);
            size_t memoria_req = (lon * (sizeof(char) + sizeof(s_item_stack_header))) + 512;
            s_arena_stack* pila_entrante = arena_stack_create(memoria_req);
            
            if (pila_entrante != NULL) {
                for (int j = (int)lon - 1; j >= 0; j--) {
                    arena_stack_push(pila_entrante, sizeof(char), &buffer_estatico[j]);
                }
                
                double result = evaluar(pila_entrante);

                // Verificamos si el resultado es un error
                if (isnan(result)) {
                    printf("ERROR NO SE PUEDE DIVIDIR ENTRE CERO\n");
                } else {
                    printf("RESULTADO: %.4f\n", result);
                }

                arena_stack_free(pila_entrante);
            }
        }

        printf("\n¿Desea realizar otra operacion? (s/n): ");

        if (scanf(" %c", &continuar) != 1) {
            continuar = 'n'; // Si falla la lectura, salimos por seguridad
        }

        // Limpiamos el buffer del teclado después del scanf
        while ((c = getchar()) != '\n' && c != EOF); 

    } while (continuar == 's' || continuar == 'S');

    return 0;
}