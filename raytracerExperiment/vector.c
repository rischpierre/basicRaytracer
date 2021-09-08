
#include "vector.h"


// todo pass args as references
struct Vector crossProduct(struct Vector v1, struct Vector v2) {
    struct Vector result;

    result.x = v1.y*v2.z - v1.z*v2.y;
    result.y = v1.z*v2.x - v1.x*v2.z;
    result.z = v1.x*v2.y - v1.y*v2.x;

    return result;
}


double dotProduct (struct Vector v1, struct Vector v2) {

    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}