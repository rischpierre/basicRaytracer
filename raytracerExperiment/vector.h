

#ifndef RAYTRACEREXPERIMENT_VECTOR_H
#define RAYTRACEREXPERIMENT_VECTOR_H
#include "vector.h"
#include "geometries.h"

Vector crossProduct(Vector *v1, Vector *v2);
float dotProduct(Vector *v1, Vector *v2);
Vector crossProductFloat(Vector *v1, float f);
Vector addVectors(Vector *v1, Vector *v2);

#endif //RAYTRACEREXPERIMENT_VECTOR_H
