#ifndef RAYTRACEREXPERIMENT_RAYTRACER_H
#define RAYTRACEREXPERIMENT_RAYTRACER_H

#include "stdbool.h"
#include "geometries.h"

bool isRayIntersectsTriangle(const Ray *ray, const Face *triangle, bool isBackFaceCulled);
float computeColor(const float *faceNormal, const DirLight* light);
void trace(Scene *scene);

#endif //RAYTRACEREXPERIMENT_RAYTRACER_H
