#ifndef RAYTRACEREXPERIMENT_RAYTRACER_H
#define RAYTRACEREXPERIMENT_RAYTRACER_H

#include "stdbool.h"
#include "geometries.h"

bool isRayIntersectsTriangle(const Ray *ray, const Face *face, float *distance);
float computeColor(const float *faceNormal, const DirLight* light);
void render(Scene *scene);
void freeScene(Scene *scene);
void splitQuads(Object *o);

#endif //RAYTRACEREXPERIMENT_RAYTRACER_H
