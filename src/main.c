#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"
#include "renderSettings.h"
#include "transform.h"

void defineExampleScene(Scene *scene) {
    Camera camera = {
            .focalPoint={0, 0, 0},
            .direction={1, 0, 0},
    };

    // light on the top left side
    DirLight light = {.direction={0.2f, 0.6f, -0.2f}};

    scene->camera = camera;
    scene->light = light;

}

void validateRenderSettings(){
    assert(RESOLUTION_DIVIDER % 2 == 0);
}

int main(int argc, char *argv[]) {
    validateRenderSettings();

    Scene *scene = malloc(sizeof(*scene));
    defineExampleScene(scene);
    char *usage = "Usage:\nraytracerExperiment <objFile>\n";
    if (argc != 2){
        printf("Wrong arguments\n");
        printf("%s", usage);
        exit(1);
    }

    parseObjFile(scene, argv[1]);

    render(scene);

    freeScene(scene);

    return 0;
}