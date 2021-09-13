

#include "raytracer.h"
#include "vector.h"
#include "stdio.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_cblas.h>

// todo install gsl lib for vectors

bool isRayIntersectsTriangle(Ray ray, Face triangle){

    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's triangle.normal
    float D = dotProduct(&triangle.normal, &triangle.v0);

    // check if triangle is parallel to ray. This can cause div by 0 instead
    if (dotProduct(&triangle.normal, &ray.direction) == 0) return false;

    // compute the distance between the triangle and the origin
    float t = (dotProduct(&triangle.normal,  &ray.origin) + D) / dotProduct(&triangle.normal, &ray.direction);


    // triangle is behind the ray
    if (t < 0 ) return false;

    Vector tmpCross = crossProductFloat(&ray.direction, t);
    Vector Phit = addVectors(&ray.origin, &tmpCross);

    // check if Phit is inside triangle
    Vector edge0 = subVectors(&triangle.v1, &triangle.v0);
    Vector C0 = subVectors(&Phit, &triangle.v0);
    Vector tmpCrossProduct = crossProduct(&edge0, &C0);

    // P is on the right side
    if (dotProduct(&triangle.normal, &tmpCrossProduct) < 0) return false;

    Vector edge1 = subVectors(&triangle.v2, &triangle.v1);
    Vector C1 = subVectors(&Phit, &triangle.v1);
    tmpCrossProduct = crossProduct(&edge1, &C1);
    if (dotProduct(&triangle.normal, &tmpCrossProduct) < 0) return false;

    Vector edge2 = subVectors(&triangle.v0, &triangle.v2);
    Vector C2 = subVectors(&Phit, &triangle.v2);
    tmpCrossProduct = crossProduct(&edge2, &C2);
    if (dotProduct(&triangle.normal, &tmpCrossProduct) < 0) return false;

    return true;
}