#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"
#include "renderSettings.h"
#include "../examples/exampleScene.h"

void validateRenderSettings(){
    assert(RESOLUTION_DIVIDER % 2 == 0 || RESOLUTION_DIVIDER == 1);
}

int main(int argc, char *argv[]) {
    validateRenderSettings();

    Scene *scene = malloc(sizeof(*scene));

    char *usage = "Usage:\nraytracerExperiment [<objFile>]\n"
                  "If no object file is provided, the example scene will be used";

    // generate scene from given .obj file
    if (argc == 2){
        // todo need to generate a basic lighting and camera here
        generateRig(scene);
        scene->isAnimated = false;
        printf("Parsing object...\n");
        parseObjFile(scene, argv[1]);

        printObject(&scene->object, false);
        printf("Rendering...\n");
        render(scene, "render.bmp");

    // animated example scene
    }else if(argc == 1){
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
            transformObject(&scene->object, scene->object.transformMatrix);
        }
        // todo try to launch ffmpeg here as a subprocess
        //ffmpeg -framerate 25 -i render.%04d.bmp -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4^C


    }else{
        printf("Wrong arguments\n");
        printf("%s", usage);
        exit(1);
    }


    freeScene(scene);

    return 0;
}