
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

#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H


#include <stdbool.h>

typedef struct {
    float origin[3];
    float direction[3];

} Ray;

typedef struct {
    float v0[3];
    float v1[3];
    float v2[3];
    float v3[3];

    bool isQuad;
    float n[3];

} Face;

typedef struct {
    Face *faces;
    int faceNb;
    const char *name;
    float worldMatrix[4][4];
} Object;

void printObject(const Object *o, bool details);

typedef struct {
    float origin[3];
    float direction[3];

} Camera;

typedef struct {
    float direction[3];

} DirLight;


typedef struct {
    DirLight light;
    Camera camera;
    Object object;
    bool isAnimated;
    unsigned int startFrame;
    unsigned int endFrame;
} Scene;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
