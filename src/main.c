#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"
#include "renderSettings.h"
#include "../examples/exampleScene.h"

void validateRenderSettings() {
    assert(RESOLUTION_DIVIDER % 2 == 0 || RESOLUTION_DIVIDER == 1);
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

        // todo test with transform here
        float translate[3] = {0, 0, 0};
        float rotate[3] = {0, 0, (2 * M_PI)/4};
        float scale[3] = {1, 1, 1};

        applyTransform(&scene->object, translate, rotate, scale);

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
            float rotate[3] = {0, 0, (2.0f * (float)M_PI)/(float)(scene->endFrame - scene->startFrame)};
            float scale[3] = {1, 1, 1};

            applyTransform(&scene->object, translate, rotate, scale);

        }
        // todo put this command in a script folder:
        //


    } else {
        printf("Wrong arguments\n");
        printf("%s", usage);
        exit(1);
    }


    freeScene(scene);

    return 0;
}