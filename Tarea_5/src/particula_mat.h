#ifndef PARTICULA_MAT_H
#define PARTICULA_MAT_H

#include "particula.h"
#include "vector/vector.h"

// Sumar partículas una a una
void particula_sumar_individual(s_particula* p1, s_particula* p2, s_particula* res);

// Suma colecciones de N partículas
void particula_sumar_coleccion_avx(s_vector* v1, s_vector* v2, s_vector* res);

// Calcula la distancia de ejes
void particula_distancia_ejes_avx(s_vector* v1, s_vector* v2, s_vector* res);

#endif