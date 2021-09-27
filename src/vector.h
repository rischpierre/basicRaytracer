

#ifndef RAYTRACEREXPERIMENT_VECTOR_H
#define RAYTRACEREXPERIMENT_VECTOR_H
#include "vector.h"
#include "geometries.h"

Vector crossProduct(Vector *v1, Vector *v2);
float dotProduct(Vector *v1, Vector *v2);
Vector crossProductFloat(Vector *v1, float f);
Vector addVectors(Vector *v1, Vector *v2);
Vector subVectors(Vector *v1, Vector *v2);
void multVectMatrix44(float *m1 , const float *m2);
float magnitude3f(Vector *v);
float angleBetweenVectors(Vector *v1, Vector *v2);

#endif //RAYTRACEREXPERIMENT_VECTOR_H
