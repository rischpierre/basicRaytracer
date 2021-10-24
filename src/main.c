#include <stdio.h>
#include <stdlib.h>
#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"

Scene defineExampleScene() {

    Camera camera = {
            .focalPoint={0, 0, 0},
            .direction={1, 0, 0},
    };

    // light on the right side
    DirLight light = {.direction={0, 1, 0}};

    Scene scene;
    scene.camera = camera;
    scene.light = light;

    return scene;
}

int main(int argc, char *argv[]) {
    Scene scene = defineExampleScene();
    char *usage = "Usage:\nraytracerExperiment <objFile>\n";
    if (argc != 2){
        printf("Wrong arguments\n");
        printf("%s", usage);
        exit(1);
    }
    parseObjFile(&scene, argv[1]);

    render(&scene);

    return 0;
}