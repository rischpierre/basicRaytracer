
/*
 *
 * Copyright (c) 2021 Pierre Risch
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of basicRaytracer.
 *
 * Author:          Pierre Risch <rischpierre@gmail.com>
 *
 */

#include "mathLib.h"
#include "math.h"
#include "stdint.h"
/*
 * Return the cross product of two vectors.
 * result:  result vector
 * v1:      first vector to compute
 * v2:      second vector to compute
 */
void crossProductVec3(float result[3], const float v1[3], const float v2[3]) {

    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];

}

/*
 * Generate a 4x4 identity matrix.
 * m: The resulting matrix
 */
void generateIdentityMat44(float m[4][4]) {

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                m[i][j] = 1;
            } else {
                m[i][j] = 0;
            }
        }
    }
}
/*
 * Multiply two matrices together.
 * m1: The first matrix to multiply to.
 * m2: The resulting matrix and the second matrix to multiply with.
 */
void multMat44(const float m1[4][4], float m2[4][4]) {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0;

            for (int k = 0; k < 4; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m2[i][j] = result[i][j];
        }
    }

}
/*
 * Return the multiplication of a 4x4 matrix with a vector
 * v: resulting vector
 * m: matrix to multiply
 */
void multV3M44(float v[3], const float m[16]) {
    float res[3];
    res[0] = v[0] * m[0] + v[1] * m[1] + v[2] * m[2] + 1 * m[3];
    res[1] = v[0] * m[4] + v[1] * m[5] + v[2] * m[6] + 1 * m[7];
    res[2] = v[0] * m[8] + v[1] * m[9] + v[2] * m[10] + 1 * m[11];

    for (int i = 0; i < 3; ++i) {
        v[i] = res[i];
    }
}

/*
 * Return the dot product of two vectors
 * v1: first vector to compute
 * v2: second vector to compute
 * return: result number of the dot product
 */
float dotProductVec3(const float v1[3], const float v2[3]) {

    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

/*
 * Return the magnitude of a vector
 * v: vector to get the magnitude of.
 * return: result magnitude of the vector
 */
float magnitudeVec3(const float v[3]) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/*
 * Return the angle between two vectors.
 * v1: first input vector
 * v2: second input vector
 * return: angle in radians
 */
float angleBetweenVec3(const float *v1, const float *v2) {

    return acosf(dotProductVec3(v1, v2) / (magnitudeVec3(v1) * magnitudeVec3(v2)));

}

/*
 * Return the cross product between a vector and a float number.
 * result: cross product result
 * v: input vector
 * f: input float
 */
void crossProductFloatVec3(float *result, const float v[3], const float *f) {
    for (uint8_t i = 0; i < 3; i++) {
        result[i] = v[i] * (*f);
    }
}

/*
 * Return the addition of two vectors.
 * result: result vector
 * v1: first input vector
 * v2: second input vector
 */
void addVec3(float *result, const float v1[3], const float v2[3]) {
    for (uint8_t i = 0; i < 3; i++) {
        result[i] = v1[i] + v2[i];
    }
}

/*
 * Return the subtraction of two vectors.
 * result: result vector
 * v1: first input vector
 * v2: second input vector
 */
void subVec3(float *result, const float *v1, const float *v2) {

    for (uint8_t i = 0; i < 3; i++) {
        result[i] = v1[i] - v2[i];
    }

}

/*
 * Compute a one dimension interpolation between
 * xValue: input value
 * inputRangeStart: start of input range
 * inputRangeEnd: end of input range
 * outputRangeStart: start of output range
 * outputRangeEnd: end of output range
 */
float interpolation1d(float inputValue, float inputRangeStart,
                      float inputRangeEnd, float outputRangeStart, float outputRangeEnd) {

    return ((outputRangeEnd - outputRangeStart) * inputValue + inputRangeEnd * outputRangeStart - inputRangeStart * outputRangeEnd) / (inputRangeEnd - inputRangeStart);

}

/*
 * Transpose a 4x4 matrix
 *
 */
// todo
void transposeM44(float result[4][4], const float input[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
            result[4 * i + j] = m44[4 * j + i];
        }
    }
}


bool invertM44(float *r_m44, const float *m) {
    float inv[16], det;
    int i;

    inv[0] = m[5] * m[10] * m[15] -
             m[5] * m[11] * m[14] -
             m[9] * m[6] * m[15] +
             m[9] * m[7] * m[14] +
             m[13] * m[6] * m[11] -
             m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] +
             m[4] * m[11] * m[14] +
             m[8] * m[6] * m[15] -
             m[8] * m[7] * m[14] -
             m[12] * m[6] * m[11] +
             m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] -
             m[4] * m[11] * m[13] -
             m[8] * m[5] * m[15] +
             m[8] * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] +
              m[4] * m[10] * m[13] +
              m[8] * m[5] * m[14] -
              m[8] * m[6] * m[13] -
              m[12] * m[5] * m[10] +
              m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] +
             m[1] * m[11] * m[14] +
             m[9] * m[2] * m[15] -
             m[9] * m[3] * m[14] -
             m[13] * m[2] * m[11] +
             m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] -
             m[0] * m[11] * m[14] -
             m[8] * m[2] * m[15] +
             m[8] * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] +
             m[0] * m[11] * m[13] +
             m[8] * m[1] * m[15] -
             m[8] * m[3] * m[13] -
             m[12] * m[1] * m[11] +
             m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] -
              m[0] * m[10] * m[13] -
              m[8] * m[1] * m[14] +
              m[8] * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] -
             m[1] * m[7] * m[14] -
             m[5] * m[2] * m[15] +
             m[5] * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] +
             m[0] * m[7] * m[14] +
             m[4] * m[2] * m[15] -
             m[4] * m[3] * m[14] -
             m[12] * m[2] * m[7] +
             m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] -
              m[0] * m[7] * m[13] -
              m[4] * m[1] * m[15] +
              m[4] * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] +
              m[0] * m[6] * m[13] +
              m[4] * m[1] * m[14] -
              m[4] * m[2] * m[13] -
              m[12] * m[1] * m[6] +
              m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
             m[1] * m[7] * m[10] +
             m[5] * m[2] * m[11] -
             m[5] * m[3] * m[10] -
             m[9] * m[2] * m[7] +
             m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
              m[0] * m[7] * m[9] +
              m[4] * m[1] * m[11] -
              m[4] * m[3] * m[9] -
              m[8] * m[1] * m[7] +
              m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0f / det;

    for (i = 0; i < 16; i++)
        r_m44[i] = inv[i] * det;

    return true;
}

