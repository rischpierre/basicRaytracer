
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

#include "transform.h"
#include "mathLib.h"
#include "renderSettings.h"
#include <math.h>
#include <stdio.h>


void applyTransform(Object *o, const float translate[3], const float rotate[3], const float scale[3]) {
    const float matrix44fTranslate[4][4] = {
            {1, 0, 0, translate[0]},
            {0, 1, 0, translate[1]},
            {0, 0, 1, translate[2]},
            {0, 0, 0, 1}

    };

    const float rxMatrix[4][4] = {
            {1, 0,               0,                0},
            {0, cosf(rotate[0]), -sinf(rotate[0]), 0},
            {0, sinf(rotate[0]), cosf(rotate[0]),  0},
            {0, 0, 0, 1}
    };

    const float ryMatrix[4][4] = {
            {cosf(rotate[1]),  0, sinf(rotate[1]), 0},
            {0,                1, 0,               0},
            {-sinf(rotate[1]), 0, cosf(rotate[1]), 0},
            {0, 0, 0, 1}
    };
    const float rzMatrix[4][4] = {
            {cosf(rotate[2]), -sinf(rotate[2]), 0, 0},
            {sinf(rotate[2]), cosf(rotate[2]),  0, 0},
            {0,               0,                1, 0},
            {0,               0,                0, 1}
    };

    const float scaleMatrix[4][4] = {
            {scale[0], 0,        0,        0},
            {0,        scale[1], 0,        0},
            {0,        0,        scale[2], 0},
            {0,        0,        0,        1}
    };

    multMat44(matrix44fTranslate, o->worldMatrix);
    multMat44(rxMatrix, o->worldMatrix);
    multMat44(ryMatrix, o->worldMatrix);
    multMat44(rzMatrix, o->worldMatrix);
    multMat44(scaleMatrix, o->worldMatrix);

}


void printBBox(const float *bbox) {

    printf("bbox: x-: %f x+ %f  |  ", bbox[0], bbox[1]);
    printf("y-: %f y+: %f  |   ", bbox[2], bbox[3]);
    printf("z-: %f z+: %f", bbox[4], bbox[5]);
    printf("\n");
}


void transformObject(Object *object) {
    // transform points
    for (int i = 0; i < object->faceNb; ++i) {
        multV3M44(object->faces[i].v0, *object->worldMatrix);
        multV3M44(object->faces[i].v1, *object->worldMatrix);
        multV3M44(object->faces[i].v2, *object->worldMatrix);
    }


    // generate the transpose of the inverse of the world matrix
    float transposeInverseMatrix[4][4], inverseMatrix[4][4];
    invertM44(*inverseMatrix, *object->worldMatrix);
    transposeM44(transposeInverseMatrix, inverseMatrix);

    // todo transform normals with the inverse transposed matrix
    for (int i = 0; i < object->faceNb; ++i) {
        multV3M44(object->faces[i].n, *transposeInverseMatrix);
    }

    // reset world matrix to avoid exponential transform
    generateIdentityMat44(object->worldMatrix);
}

void computeBBox(const Object *o, float *bbox) {

    float maxCoordX = -WORLD_MAX_DISTANCE;
    float maxCoordY = -WORLD_MAX_DISTANCE;
    float maxCoordZ = -WORLD_MAX_DISTANCE;

    float minCoordX = WORLD_MAX_DISTANCE;
    float minCoordY = WORLD_MAX_DISTANCE;
    float minCoordZ = WORLD_MAX_DISTANCE;

    Face *current;
    for (int i = 0; i < o->faceNb; i++) {
        current = &o->faces[i];

        // loop over every vertex in the face
        for (int v = 0; v < 3; v++) {
            // loop over attributes of struct
            float x = *(current->v0 + 3 * v + 0);
            float y = *(current->v0 + 3 * v + 1);
            float z = *(current->v0 + 3 * v + 2);

            if (x < minCoordX)
                minCoordX = x;
            if (x > maxCoordX)
                maxCoordX = x;

            if (y < minCoordY)
                minCoordY = y;
            if (y > maxCoordY)
                maxCoordY = y;

            if (z < minCoordZ)
                minCoordZ = z;
            if (z > maxCoordZ)
                maxCoordZ = z;
        }
    }

    bbox[0] = minCoordX;
    bbox[1] = maxCoordX;

    bbox[2] = minCoordY;
    bbox[3] = maxCoordY;

    bbox[4] = minCoordZ;
    bbox[5] = maxCoordZ;

}
