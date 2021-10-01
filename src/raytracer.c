

#include "raytracer.h"
#include "mathLib.h"
#include "stdio.h"


bool isRayIntersectsTriangle(const Ray *ray, const Face *face){

    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's triangle.normal
    float D = dotProduct(face->normal, face->v0);

    // check if triangle is parallel to ray. This can cause div by 0 instead
    if (dotProduct(face->normal, ray->direction) == 0) return false;

    // compute the distance between the triangle and the origin
    float t = (dotProduct(face->normal,  ray->origin) + D) / dotProduct(face->normal, ray->direction);


    // triangle is behind the ray
    if (t < 0 ) return false;

    float tmpCross[3];

    crossProductFloat(tmpCross, ray->direction, &t);
    float Phit[3];

    addVectors(Phit, ray->origin, tmpCross);

    // check if Phit is inside triangle
    float edge0[3];
    subVectors(edge0, face->v1, face->v0);

    float C0[3];
    subVectors(C0, Phit, face->v0);

    float tmpCrossProduct[3];
    crossProduct(tmpCrossProduct, edge0, C0);

    // P is on the right side
    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    float edge1[3];
    subVectors(edge1, face->v2, face->v1);

    float C1[3];
    subVectors(C1, Phit, face->v1);

    crossProduct(tmpCrossProduct, edge1, C1);

    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    float edge2[3];
    subVectors(edge2, face->v0, face->v2);

    float C2[3];
    subVectors(C2, Phit, face->v2);

    crossProduct(tmpCrossProduct, edge2, C2);
    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    return true;
}