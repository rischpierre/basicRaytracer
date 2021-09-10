
#include "vector.h"


// todo pass args as references
Vector crossProduct(Vector *v1, Vector *v2) {
    Vector result;

    result.x = v1->y*v2->z - v1->z*v2->y;
    result.y = v1->z*v2->x - v1->x*v2->z;
    result.z = v1->x*v2->y - v1->y*v2->x;

    return result;
}


double dotProduct (Vector *v1, Vector *v2) {

    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}