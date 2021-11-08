
#ifndef RAYTRACEREXPERIMENT_TRANSFORM_H
#define RAYTRACEREXPERIMENT_TRANSFORM_H

#include "geometries.h"

void printBBox(const float *bbox);

void transformVec3(float *v, float *tm);

void computeBBox(const Object *o, float *bbox);

void transformObject(Object *o);

void applyTransform(Object *o, const float translate[3], const float rotate[3], const float scale[3]);

#endif //RAYTRACEREXPERIMENT_TRANSFORM_H

