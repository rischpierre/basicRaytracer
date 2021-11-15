
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
 *
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
 *
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
 *
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
 *
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
 *
 * v1: first vector to compute
 * v2: second vector to compute
 * return: result number of the dot product
 */
float dotProductVec3(const float v1[3], const float v2[3]) {

    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

/*
 * Return the magnitude of a vector
 *
 * v: vector to get the magnitude of.
 * return: result magnitude of the vector
 */
float magnitudeVec3(const float v[3]) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/*
 * Return the angle between two vectors.
 *
 * v1: first input vector
 * v2: second input vector
 * return: angle in radians
 */
float angleBetweenVec3(const float *v1, const float *v2) {

    return acosf(dotProductVec3(v1, v2) / (magnitudeVec3(v1) * magnitudeVec3(v2)));

}

/*
 * Return the cross product between a vector and a float number.
 *
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
 *
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
 *
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
 *
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
 * Transpose a 4x4 matrix.
 *
 * result: The transposed matrix.
 * input: The matrix to transpose.
 */
void transposeM44(float result[4][4], const float input[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = input[j][i];
        }
    }
}

/*
 * Invert a 4x4 matrix if possible.
 * It returns false if the inversion is not possible.
 *
 * result: The resulting matrix.
 * input: The input matrix to invert.
 * result: true if it is possible to invert.
 */
bool invertM44(float *result, const float *input) {
    float inv[16], det;
    // todo replace all the [] with double [][]
    inv[0] = input[5] * input[10] * input[15] -
             input[5] * input[11] * input[14] -
             input[9] * input[6] * input[15] +
             input[9] * input[7] * input[14] +
             input[13] * input[6] * input[11] -
             input[13] * input[7] * input[10];

    inv[4] = -input[4] * input[10] * input[15] +
             input[4] * input[11] * input[14] +
             input[8] * input[6] * input[15] -
             input[8] * input[7] * input[14] -
             input[12] * input[6] * input[11] +
             input[12] * input[7] * input[10];

    inv[8] = input[4] * input[9] * input[15] -
             input[4] * input[11] * input[13] -
             input[8] * input[5] * input[15] +
             input[8] * input[7] * input[13] +
             input[12] * input[5] * input[11] -
             input[12] * input[7] * input[9];

    inv[12] = -input[4] * input[9] * input[14] +
              input[4] * input[10] * input[13] +
              input[8] * input[5] * input[14] -
              input[8] * input[6] * input[13] -
              input[12] * input[5] * input[10] +
              input[12] * input[6] * input[9];

    inv[1] = -input[1] * input[10] * input[15] +
             input[1] * input[11] * input[14] +
             input[9] * input[2] * input[15] -
             input[9] * input[3] * input[14] -
             input[13] * input[2] * input[11] +
             input[13] * input[3] * input[10];

    inv[5] = input[0] * input[10] * input[15] -
             input[0] * input[11] * input[14] -
             input[8] * input[2] * input[15] +
             input[8] * input[3] * input[14] +
             input[12] * input[2] * input[11] -
             input[12] * input[3] * input[10];

    inv[9] = -input[0] * input[9] * input[15] +
             input[0] * input[11] * input[13] +
             input[8] * input[1] * input[15] -
             input[8] * input[3] * input[13] -
             input[12] * input[1] * input[11] +
             input[12] * input[3] * input[9];

    inv[13] = input[0] * input[9] * input[14] -
              input[0] * input[10] * input[13] -
              input[8] * input[1] * input[14] +
              input[8] * input[2] * input[13] +
              input[12] * input[1] * input[10] -
              input[12] * input[2] * input[9];

    inv[2] = input[1] * input[6] * input[15] -
             input[1] * input[7] * input[14] -
             input[5] * input[2] * input[15] +
             input[5] * input[3] * input[14] +
             input[13] * input[2] * input[7] -
             input[13] * input[3] * input[6];

    inv[6] = -input[0] * input[6] * input[15] +
             input[0] * input[7] * input[14] +
             input[4] * input[2] * input[15] -
             input[4] * input[3] * input[14] -
             input[12] * input[2] * input[7] +
             input[12] * input[3] * input[6];

    inv[10] = input[0] * input[5] * input[15] -
              input[0] * input[7] * input[13] -
              input[4] * input[1] * input[15] +
              input[4] * input[3] * input[13] +
              input[12] * input[1] * input[7] -
              input[12] * input[3] * input[5];

    inv[14] = -input[0] * input[5] * input[14] +
              input[0] * input[6] * input[13] +
              input[4] * input[1] * input[14] -
              input[4] * input[2] * input[13] -
              input[12] * input[1] * input[6] +
              input[12] * input[2] * input[5];

    inv[3] = -input[1] * input[6] * input[11] +
             input[1] * input[7] * input[10] +
             input[5] * input[2] * input[11] -
             input[5] * input[3] * input[10] -
             input[9] * input[2] * input[7] +
             input[9] * input[3] * input[6];

    inv[7] = input[0] * input[6] * input[11] -
             input[0] * input[7] * input[10] -
             input[4] * input[2] * input[11] +
             input[4] * input[3] * input[10] +
             input[8] * input[2] * input[7] -
             input[8] * input[3] * input[6];

    inv[11] = -input[0] * input[5] * input[11] +
              input[0] * input[7] * input[9] +
              input[4] * input[1] * input[11] -
              input[4] * input[3] * input[9] -
              input[8] * input[1] * input[7] +
              input[8] * input[3] * input[5];

    inv[15] = input[0] * input[5] * input[10] -
              input[0] * input[6] * input[9] -
              input[4] * input[1] * input[10] +
              input[4] * input[2] * input[9] +
              input[8] * input[1] * input[6] -
              input[8] * input[2] * input[5];

    det = input[0] * inv[0] + input[1] * inv[4] + input[2] * inv[8] + input[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0f / det;

    for (int i = 0; i < 16; i++)
        result[i] = inv[i] * det;

    return true;
}

