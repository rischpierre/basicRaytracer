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

#ifndef RAYTRACEREXPERIMENT_IOLIB_H
#define RAYTRACEREXPERIMENT_IOLIB_H

#include "geometries.h"

#define TAG_VERTEX "v "
#define TAG_VERTEX_N "vn "
#define TAG_FACE "f "
#define TAG_OBJECT "o "
#define BUFFER_SIZE 256

// the image origin is the bottom left corner
void writeBmpFile(int width, int height, float **red, float **green, float **blue, const char *filePath);

void parseObjFile(Scene *scene, const char *filePath);

void splitFaceToken(const char *token, int *vertexId, int *vertexNId);

void parseVertices(float *vertices, const char *buffer, const int *vertexId);

Face parseFace(const char *buffer, const float *vertices, const float *vertexNormals);

#endif //RAYTRACEREXPERIMENT_IOLIB_H