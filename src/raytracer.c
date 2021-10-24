

#include <math.h>
#include "raytracer.h"
#include "mathLib.h"
#include "renderSettings.h"


bool isRayIntersectsTriangle(const Ray *ray, const Face *face, bool isBackFaceCulled){

    // skip if the face is back
    if (dotProduct(ray->direction, face->normal) > 0 && isBackFaceCulled){
        return false;
    }

    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's triangle.normal
    float D = dotProduct(face->normal, face->v0);

    float NDotRayDirection = dotProduct(face->normal, ray->direction);
    // check if triangle is parallel to ray. This can cause div by 0 instead
    if (NDotRayDirection == 0) return false;

    // compute the distance between the triangle and the origin of the ray
    float t = -(dotProduct(face->normal,  ray->origin) + (float)fabs((double)D)) / NDotRayDirection;

    // triangle is behind the ray
    if (t < 0 ) return false;

    float tmpCross[3];

    crossProductFloat(tmpCross, ray->direction, &t, 3);
    float Phit[3];

    addVectors(Phit, ray->origin, tmpCross, 3);

    // check if Phit is inside triangle
    float edge0[3];
    subVectors(edge0, face->v1, face->v0, 3);

    float C0[3];
    subVectors(C0, Phit, face->v0, 3);

    float tmpCrossProduct[3];
    crossProduct(tmpCrossProduct, edge0, C0);

    // P is on the right side
    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    float edge1[3];
    subVectors(edge1, face->v2, face->v1, 3);

    float C1[3];
    subVectors(C1, Phit, face->v1, 3);

    crossProduct(tmpCrossProduct, edge1, C1);

    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    float edge2[3];
    subVectors(edge2, face->v0, face->v2, 3);

    float C2[3];
    subVectors(C2, Phit, face->v2, 3);

    crossProduct(tmpCrossProduct, edge2, C2);
    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    return true;
}


float computeColor(const float *faceNormal, const DirLight *light) {
    float angle = angleBetweenVectors(light->direction, faceNormal);
    float result = interpolation1d(angle, M_PI / 2, M_PI, 0, 1);
    if (result < 0){
        return ambientContribution;
    }
    return result;
}