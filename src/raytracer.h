//
// Created by pierre on 2021-09-10.
//

#ifndef RAYTRACEREXPERIMENT_RAYTRACER_H
#define RAYTRACEREXPERIMENT_RAYTRACER_H

#include "stdbool.h"
#include "geometries.h"

bool isRayIntersectsTriangle(const Ray *ray, const Face *triangle);

#endif //RAYTRACEREXPERIMENT_RAYTRACER_H
