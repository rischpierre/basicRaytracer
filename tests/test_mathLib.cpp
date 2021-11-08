
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

#include <math.h>
#include "../src/mathLib.h"

#include "gtest/gtest.h"


TEST(vector_tests, cross_product) {
    float v1[3] = {1, 0, 0};
    float v2[3] = {0, 1, 0};
    float result[3];

    crossProduct(result, v1, v2);
    float expected[3] = {0, 0, 1};

    for (uint8_t i = 0; i < 3; i++) {

        ASSERT_FLOAT_EQ(expected[i], result[i]);
    }
}

TEST(vector_tests, mult_matrix) {

    float matrix44fTranslate[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 2, 2, 1};
    float vector[4] = {1, 1, 1, 1};
    float vectorExpected[4] = {3, 3, 3, 1};

    multV33M44(vector, matrix44fTranslate);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(vector[i], vectorExpected[i]);
    }
}

TEST(vector_tests, dot_product) {
    float v1[3] = {1, 1, 2};
    float v2[3] = {0, 1, 4};
    ASSERT_EQ(dotProduct(v1, v2), 9);
}

TEST(vector_tests, angle_between_vectors) {
    float v1[3] = {1, 0, 0};
    float v2[3] = {0, 1, 0};
    float v3[3] = {-1, 0, 0};

    ASSERT_EQ(angleBetweenVectors(v1, v2), (float) M_PI / 2);
    ASSERT_EQ(angleBetweenVectors(v1, v1), 0);
    ASSERT_EQ(angleBetweenVectors(v1, v3), (float) M_PI);
}

TEST(utils, interpolation1d) {

    ASSERT_EQ(interpolation1d(50, 0, 100, -3, 3), 0.0);
    ASSERT_EQ(interpolation1d(10, 0, 100, -10, 10), -8);
}

TEST(transpose, transposeMatrix) {

    float m[16] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16

    };

    float exp[16] = {
            1, 5, 9, 13,
            2, 6, 10, 14,
            3, 7, 11, 15,
            4, 8, 12, 16
    };
    float res[16] = {0};
    transposeM44(res, m);
    for (int i = 0; i < 16; ++i) {
        ASSERT_EQ(res[i], exp[i]);
    }
}

TEST(matrixTests, inverseMatrix) {
    float m[16] = {
            2, 0, 0, 0,
            0, 1, 4, 0,
            5, 0, 1, 0,
            0, 0, 0, 1
    };

    float exp[16] = {
            0.5f, 0, 0, 0,
            10, 1, -4, 0,
            -5.0 / 2, 0, 1, 0,
            0, 0, 0, 1

    };
    float result[16];
    invertM44(result, m);
    for (int i = 0; i < 16; ++i) {
        ASSERT_EQ(result[i], exp[i]);
    }
}



