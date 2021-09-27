
#include "vector.h"
#include "math.h"

// todo pass args as references
Vector crossProduct(Vector *v1, Vector *v2) {
    Vector result;

    result.x = v1->y*v2->z - v1->z*v2->y;
    result.y = v1->z*v2->x - v1->x*v2->z;
    result.z = v1->x*v2->y - v1->y*v2->x;

    return result;
}

void multVectMatrix44(float *m1 , const float *m2) {

    for(int i=0; i < 4; i++) {

        m1[i] = m1[0] * m2[i] + m1[1] * m2[i+4] + m1[2] * m2[i+8] + m1[3] * m2[i+12];

    }

}

float magnitude3f(Vector *v){
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

float angleBetweenVectors(Vector *v1, Vector *v2) {

    return acosf(dotProduct(v1, v2) / (magnitude3f(v1) * magnitude3f(v2)));

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