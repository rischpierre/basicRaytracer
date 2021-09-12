

#include "raytracer.h"
#include "vector.h"
#include "stdio.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_cblas.h>

// todo install gsl lib for vectors

bool isRayIntersectsTriangle(Ray ray, Face triangle){

    gsl_vector * v1 = gsl_vector_alloc(3);
    gsl_vector * v2 = gsl_vector_alloc(3);


    gsl_vector_set(v1, 0, 1);
    gsl_vector_set(v1, 1, 0);
    gsl_vector_set(v1, 2, 0);

    gsl_vector_set(v2, 0, 0);
    gsl_vector_set(v2, 1, 1);
    gsl_vector_set(v2, 2, 0);

//    gsl_vector *v3 = gsl_vector_alloc(3);

//    gsl_vector_mul(v1, v2); cross product
    gsl_vector_sub(v1, v2);

    gsl_vector_fprintf(stdout, v1, "%g");



    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's normal
    float D = dotProduct(&triangle.normal, &triangle.v0);

    // compute the distance between the triangle and the origin
    float t = -(dotProduct(&triangle.normal,  &ray.origin) + D) / dotProduct(&triangle.normal, &ray.direction);

    // todo the PHit calue is not valid here, it should be 2, 0, 0
    // todo install lib for vectors
    Vector tmpCross = crossProductFloat(&ray.direction, t);
    Vector Phit = addVectors(&ray.origin, &tmpCross);


    return false;
}