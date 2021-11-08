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

#include "gtest/gtest.h"


TEST(computeBbox, validBBox){

    float bbox[6];

    Face faces[1];
    const char *name = "test";
    Object o;
    o.faces = faces;
    o.faceNb = 1;
    o.name = name;

    Face f = {
            {1, 2, -3},
            {-4, 5, 6},
            {7, 8, 9},
            {0, 1, 0},
            false,
            {0, 1, 0}
    };
    faces[0] = f;

    computeBBox(&o, bbox);

    ASSERT_FLOAT_EQ(bbox[0], -4);
    ASSERT_FLOAT_EQ(bbox[1], 7);

    ASSERT_FLOAT_EQ(bbox[2], 2);
    ASSERT_FLOAT_EQ(bbox[3], 8);

    ASSERT_FLOAT_EQ(bbox[4], -3);
    ASSERT_FLOAT_EQ(bbox[5], 9);
}
