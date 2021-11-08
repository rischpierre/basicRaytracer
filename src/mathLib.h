

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

#ifndef RAYTRACEREXPERIMENT_MATHLIB_H
#define RAYTRACEREXPERIMENT_MATHLIB_H

#include "mathLib.h"
#include "geometries.h"
#include "stdint.h"

void crossProduct(float *result, const float *v1, const float *v2);

void multM44M44(const float m1[4][4], float m2[4][4]);

void initIdentityM44(float m[4][4]);

float dotProduct(const float *v1, const float *v2);

float magnitude3f(const float *v);

float angleBetweenVectors(const float *v1, const float *v2);

void crossProductFloat(float *result, const float *v1, const float *f);

void addVectors(float *result, const float *v1, const float *v2);

void subVectors(float *result, const float *v1, const float *v2);

float interpolation1d(float x, float x1, float x2, float y1, float y2);

void transposeM44(float *r_m44, const float *m44);

bool invertM44(float *r_m44, const float *m44);

void multV33M44(float v[3], const float m[16]);

#endif //RAYTRACEREXPERIMENT_MATHLIB_H
