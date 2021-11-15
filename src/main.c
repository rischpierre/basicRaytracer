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
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sceneEntities.h"
#include "raytracer.h"
#include "ioLib.h"
#include "renderSettings.h"
#include "../examples/exampleScene.h"


/*
 * Check if all the render settings are valid
 */
void validateRenderSettings() {
    static_assert(RESOLUTION_DIVIDER % 2 == 0 || RESOLUTION_DIVIDER == 1);
}

int main(int argc, char *argv[]) {
    validateRenderSettings();

    Scene *scene = malloc(sizeof(*scene));

    char *usage = "Usage:\nraytracerExperiment [<objFile>]\n"
                  "If no object file is provided, the example scene will be used";

    // generate scene from given .obj file
    if (argc == 2) {
        generateRig(scene);
        scene->isAnimated = false;
        printf("Parsing object...\n");
        parseObjFile(scene, argv[1]);

        printObject(&scene->object, false);
        printf("Rendering...\n");

        render(scene, "render.bmp");

        // animated example scene
    } else if (argc == 1) {
        generateExampleScene(scene);

        printObject(&scene->object, false);

        for (unsigned int frame = scene->startFrame; frame <= scene->endFrame; ++frame) {
            printf("Rendering frame %d ...\n", frame);

            char frameStr[5];
            char imageName[50] = "render.";

            sprintf(frameStr, "%04d", frame);
            strcat(imageName, frameStr);
            strcat(imageName, ".bmp");

            render(scene, imageName);

            // todo move it in the example scene
            float translate[3] = {0, 0, 0};
            float rotate[3] = {0, 0, (2.0f * (float) M_PI) / (float) (scene->endFrame - scene->startFrame)};
            float scale[3] = {1, 1, 1};

            applyTransform(&scene->object, translate, rotate, scale);
        }

    } else {
        printf("Wrong arguments\n");
        printf("%s", usage);
        exit(1);
    }

    freeScene(scene);

    return 0;
}
