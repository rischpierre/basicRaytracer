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
    unsigned int frameNb = FPS * 2;
    generateRig(scene);
    scene->isAnimated = true;
    scene->startFrame = 1;
    scene->endFrame = scene->startFrame + frameNb;
    parseObjFile(scene, "../examples/monkey.obj");

    float transformControls[9] = {
           0, 0, 0,
           0, 0, 2 * M_PI / frameNb,
           1, 1, 1
    };
}

#endif //RAYTRACEREXPERIMENT_EXAMPLESCENE_H
