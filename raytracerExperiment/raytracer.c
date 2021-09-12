

#include "raytracer.h"
#include "vector.h"
#include "stdio.h"

// todo install gsl lib for vectors

bool isRayIntersectsTriangle(Ray ray, Face triangle){


    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's normal
    float D = dotProduct(&triangle.normal, &triangle.v0);

    // compute the distance between the triangle and the origin
    float t = -(dotProduct(&triangle.normal,  &ray.origin) + D) / dotProduct(&triangle.normal, &ray.direction);


    // todo the PHit calue is not valid here, it should be 0, 2, 0
    Vector tmpCross = crossProductFloat(&ray.direction, t);
    Vector Phit = addVectors(&ray.origin, &tmpCross);


    return false;
}