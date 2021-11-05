
#ifndef RAYTRACEREXPERIMENT_TRANSFORM_H
#define RAYTRACEREXPERIMENT_TRANSFORM_H

#include "geometries.h"

void printBBox(const float* bbox);
void transform(float *v, float *tm);
void computeBBox(const Object *o, float* bbox);
void transformObject(Object *o, float* tm);

#endif //RAYTRACEREXPERIMENT_TRANSFORM_H
