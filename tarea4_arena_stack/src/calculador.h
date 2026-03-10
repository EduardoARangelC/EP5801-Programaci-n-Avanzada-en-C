#ifndef CALCULADOR_H
#define CALCULADOR_H

#include "./arena/arena_stack.h"

// Recibe la arena que contiene los caracteres de la operación
double evaluar(s_arena_stack* pila_entrante);

// Devuelve la prioridad de un operador
int prioridad(char op);

// Función para ejecutar la operación
double efectuar_operacion(double a, double b, char op);

#endif