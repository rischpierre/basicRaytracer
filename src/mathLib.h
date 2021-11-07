

#ifndef RAYTRACEREXPERIMENT_MATHLIB_H
#define RAYTRACEREXPERIMENT_MATHLIB_H

#include "mathLib.h"
#include "geometries.h"
#include "stdint.h"

void crossProduct(float *result, const float *v1, const float *v2);

void multM44M44(const float m1[4][4], float m2[4][4]);

void initIdentityM44(float m[4][4]);

float dotProduct(const float *v1, const float *v2);

float magnitude3f(const float *v);

float angleBetweenVectors(const float *v1, const float *v2);

void crossProductFloat(float *result, const float *v1, const float *f, uint8_t size);

void addVectors(float *result, const float *v1, const float *v2, uint8_t size);

void subVectors(float *result, const float *v1, const float *v2, uint8_t size);

float interpolation1d(float x, float x1, float x2, float y1, float y2);

void transposeM44(float *r_m44, const float *m44);

bool invertM44(float *r_m44, const float *m44);

#endif //RAYTRACEREXPERIMENT_MATHLIB_H
