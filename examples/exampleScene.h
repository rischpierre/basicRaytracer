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

#ifndef RAYTRACEREXPERIMENT_EXAMPLESCENE_H
#define RAYTRACEREXPERIMENT_EXAMPLESCENE_H


#include <math.h>
#include "../src/geometries.h"
#include "../src/transform.h"

void generateRig(Scene *scene) {

    Camera camera = {
            .origin={0, -5, 0},
            .direction={0, 0, 0},
    };

    // light on the top left side
    DirLight light = {.direction={0.2f, 0.6f, -0.2f}};

    scene->camera = camera;
    scene->light = light;
}


void generateExampleScene(Scene *scene) {
    generateRig(scene);
    scene->isAnimated = true;
    scene->startFrame = 1;
    scene->endFrame = 24 * 2;
    parseObjFile(scene, "../examples/monkey.obj");

}

#endif //RAYTRACEREXPERIMENT_EXAMPLESCENE_H
