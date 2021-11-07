

#ifndef RAYTRACEREXPERIMENT_MATHLIB_H
#define RAYTRACEREXPERIMENT_MATHLIB_H
#include "mathLib.h"
#include "geometries.h"
#include "stdint.h"

void crossProduct(float* result, const float *v1, const float *v2);
void multVectMatrix44(float *m1 , const float *m2);
float dotProduct(const float *v1, const float *v2);
float magnitude3f(const float *v);
float angleBetweenVectors(const float *v1, const float *v2);
void crossProductFloat(float* result, const float *v1, const float *f);
void addVectors(float *result, const float *v1, const float *v2);
void subVectors(float *result, const float *v1, const float *v2);
float interpolation1d(float x, float x1, float x2, float y1, float y2);

#endif //RAYTRACEREXPERIMENT_MATHLIB_H
