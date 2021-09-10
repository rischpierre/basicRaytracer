

#include "raytracer.h"
#include "vector.h"

bool isRayIntersectsTriangle(Ray ray, Face triangle){


    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's normal

    float D = dotProduct(&triangle.normal, &triangle.v0);
    return false;
}