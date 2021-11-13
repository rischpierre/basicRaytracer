
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

#include <stdio.h>
#include "sceneEntities.h"


void printObject(const Object *o, bool details) {
    printf("Object: %s\n", o->name);
    printf("nb of faces: %d\n", o->faceNb);
    if (details == true) {
        for (int faceId = 0; faceId < o->faceNb; faceId++) {
            printf("----------------------\n");
            Face curr = o->faces[faceId];
            printf("Face %d\n", faceId);
            printf("  v0: %f %f %f\n", curr.v0[0], curr.v0[1], curr.v0[2]);
            printf("  v1: %f %f %f\n", curr.v1[0], curr.v1[1], curr.v1[2]);
            printf("  v2: %f %f %f\n", curr.v2[0], curr.v2[1], curr.v2[2]);
            printf("  n:  %f %f %f\n", curr.n[0], curr.n[1], curr.n[2]);
        }
    }
    printf("----------------------\n");
}
