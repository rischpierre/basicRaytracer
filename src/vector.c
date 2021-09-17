
#include "vector.h"


// todo pass args as references
Vector crossProduct(Vector *v1, Vector *v2) {
    Vector result;

    result.x = v1->y*v2->z - v1->z*v2->y;
    result.y = v1->z*v2->x - v1->x*v2->z;
    result.z = v1->x*v2->y - v1->y*v2->x;

    return result;
}


float dotProduct (Vector *v1, Vector *v2) {

    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}


Vector crossProductFloat(Vector *v1, float f) {
    Vector result;

    result.x = v1->x*f;
    result.y = v1->y*f;
    result.z = v1->z*f;

    return result;
}

Vector addVectors(Vector *v1, Vector *v2) {
    Vector result;

    result.x = v1->x + v2->x;
    result.y = v1->y + v2->y;
    result.z = v1->z + v2->z;

    return result;

}

Vector subVectors(Vector *v1, Vector *v2) {
    Vector result;

    result.x = v1->x - v2->x;
    result.y = v1->y - v2->y;
    result.z = v1->z - v2->z;

    return result;

}