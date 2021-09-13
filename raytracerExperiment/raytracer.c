

#include "raytracer.h"
#include "vector.h"
#include "stdio.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_cblas.h>

// todo install gsl lib for vectors

bool isRayIntersectsTriangle(Ray ray, Face triangle){


    // calculate face normal, discard normal from triangle?
    Vector v0v1 = subVectors(&triangle.v1, &triangle.v0);
    Vector v0v2 = subVectors(&triangle.v2, &triangle.v0);
    Vector Normal = crossProduct(&v0v1, &v0v2);

    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's normal
    float D = dotProduct(&Normal, &triangle.v0);

    // check if triangle is parrallel to ray. This can cause div by 0 instead
    if (dotProduct(&Normal, &ray.direction) == 0) return false;

    // compute the distance between the triangle and the origin
    float t = (dotProduct(&Normal,  &ray.origin) + D) / dotProduct(&Normal, &ray.direction);


    // triangle is behind the ray
    if (t < 0 ) return false;

    Vector tmpCross = crossProductFloat(&ray.direction, t);
    Vector Phit = addVectors(&ray.origin, &tmpCross);


    return false;
}