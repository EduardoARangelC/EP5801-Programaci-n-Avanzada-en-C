#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "calculador.h"

// Función para determinar la prioridad de los operadores
int prioridad(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Función para realizar la operación entre dos números según el operador
double efectuar_operacion(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) return NAN;
            return a / b;
        default: return 0.0;
    }
}

// El cerebro, esta funcion evalua la expresión dada
double evaluar(s_arena_stack* pila_entrante) {
    if (!pila_entrante || pila_entrante->offset == 0) return 0.0; // Si la pila es nula o esta vacía, retorna 0

    // Arenas temporales para el cálculo
    s_arena_stack* valores = arena_stack_create(1024);
    s_arena_stack* ops = arena_stack_create(512);

    char c; // carácter temporal que estamos analizando
    char buffer_num[32]; // buffer para construir los números a medida que los leemos
    int idx_num = 0;
    int procesando_numero = 0;

    // Procesamos la pila de caracteres
    while (arena_stack_pop(pila_entrante, &c) != NULL) {
        if (isspace(c)) continue; // Ignoramos espacios
        // Si es un numero o un punto, lo agregamos lo guardamos al buffer del número
        if (isdigit(c) || c == '.') {
            buffer_num[idx_num++] = c;
            procesando_numero = 1;
        } else {
            // Si veníamos leyendo un número, lo guardamos antes de procesar el operador
            if (procesando_numero) {
                buffer_num[idx_num] = '\0';
                double num = atof(buffer_num);
                arena_stack_push(valores, sizeof(double), &num);
                idx_num = 0;
                procesando_numero = 0;
            }
            // logica para la prioridad de los operadores
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                char op_tope;
                // Revisamos la prioridad de los operadores en la pila
                while (arena_stack_pop(ops, &op_tope) != NULL) {
                    if (prioridad(op_tope) >= prioridad(c)) { // Si el operador en la pila tiene mayor o igual prioridad, lo aplicamos
                        double v1, v2;
                        if (arena_stack_pop(valores, &v2) != NULL && arena_stack_pop(valores, &v1) != NULL) {
                            double res = efectuar_operacion(v1, v2, op_tope);
                            arena_stack_push(valores, sizeof(double), &res);
                        }
                    } else {
                        // Si no es mayor prioridad, lo devolvemos a la pila y paramos
                        arena_stack_push(ops, sizeof(char), &op_tope);
                        break;
                    }
                }
                arena_stack_push(ops, sizeof(char), &c);
            }
        }
    }

    // Guardamos el último número si quedó pendiente
    if (procesando_numero) {
        buffer_num[idx_num] = '\0';
        double num = atof(buffer_num);
        arena_stack_push(valores, sizeof(double), &num);
    }

    // Vaciar los operadores restantes
    char op_final;
    while (arena_stack_pop(ops, &op_final) != NULL) {
        double v1, v2;
        if (arena_stack_pop(valores, &v2) != NULL && arena_stack_pop(valores, &v1) != NULL) {
            double res = efectuar_operacion(v1, v2, op_final);
            arena_stack_push(valores, sizeof(double), &res);
        }
    }

    // Extraemos el resultado final que es el ultimo valor de la pila de valores
    double resultado_total = 0.0;
    arena_stack_pop(valores, &resultado_total);

    // Liberamos las arenas temporales
    arena_stack_free(valores);
    arena_stack_free(ops);

    return resultado_total;
}