
#include "mathLib.h"
#include "math.h"
#include "stdint.h"

void crossProduct(float* result, const float *v1, const float* v2) {

    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];

}

void multVectMatrix44(float *m1 , const float *m2) {

    for(int i=0; i < 4; i++) {

        m1[i] = m1[0] * m2[i] + m1[1] * m2[i+4] + m1[2] * m2[i+8] + m1[3] * m2[i+12];

    }

}

float dotProduct(const float *v1, const float *v2) {

    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


float magnitude3f(const float *v){
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float angleBetweenVectors(const float *v1, const float *v2) {

    return acosf(dotProduct(v1, v2) / (magnitude3f(v1) * magnitude3f(v2)));

}


void crossProductFloat(float *result, const float *v1, const float *f) {
    for (uint8_t i = 0; i < 3; i++){
        result[i] = v1[i] * (*f);

    }
}

void addVectors(float* result, const float *v1, const float *v2) {
    for (uint8_t i = 0; i < 2; i++){
        result[i] = v1[i] + v2[i];
    }

}

void subVectors(float *result, const float *v1, const float *v2) {

    for (uint8_t i = 0; i < 2; i++){
        result[i] = v1[i] - v2[i];
    }

}


float interpolation1d(float x, float x1, float x2, float y1, float y2){

    return ((y2 - y1) * x + x2 * y1 - x1 * y2) / (x2 - x1);

}