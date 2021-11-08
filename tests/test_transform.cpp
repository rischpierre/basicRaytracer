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

#include "../src/transform.h"

#include <math.h>

#include "gtest/gtest.h"


TEST(transformTests, translate_works) {
    float v[4] = {0, 0, 0, 1};

    float transformMatrix[9] = {
            2, 4, -2,            // translate
            0, 0, 0,            // rotate in rads: M_PI/4
            1.f, 1.f, 1.f       // scale
    };

    transformVec3(v, transformMatrix);

    float expected[4] = {2, 4, -2, 1};

    for(uint8_t i = 0; i < 4; i++){

        ASSERT_FLOAT_EQ(expected[i], v[i]);
    }
}


TEST(transformTests, rotate_works) {
    float v[4] = {1, 0, 0, 1};

    float transformMatrix[9] = {
            0, 0, 0,
            0, M_PI/4, 0,
            1.f, 1.f, 1.f
    };

    transformVec3(v, transformMatrix);

    float expected[4] = {cosf(M_PI/4), 0, 0.5f, 1.f};

    for(uint8_t i = 0; i < 4; i++){

        ASSERT_FLOAT_EQ(expected[i], v[i]);
    }

}

TEST(transformTests, scale_works) {
    float v[4] = {1, 1, 1, 1};

    float transformMatrix[9] = {
            0, 0, 0,
            0, 0, 0,
            .5f, .5f, .5f
    };

    transformVec3(v, transformMatrix);

    float expected[4] = {0.5f, 0.5f, 0.5f, 1.f};
    for(uint8_t i = 0; i < 4; i++){

        ASSERT_FLOAT_EQ(expected[i], v[i]);
    }

}

TEST(computeBbox, validBBox){

    float bbox[6];

    Face faces[1];
    Object o = {.faces=faces, .faceNb=1, .name="test"};
    Face f = {.v0={1, 2, -3}, .v1={-4, 5, 6}, .v2={7, 8, 9}};
    faces[0] = f;

    computeBBox(&o, bbox);

    ASSERT_FLOAT_EQ(bbox[0], -4);
    ASSERT_FLOAT_EQ(bbox[1], 7);

    ASSERT_FLOAT_EQ(bbox[2], 2);
    ASSERT_FLOAT_EQ(bbox[3], 8);

    ASSERT_FLOAT_EQ(bbox[4], -3);
    ASSERT_FLOAT_EQ(bbox[5], 9);
}
