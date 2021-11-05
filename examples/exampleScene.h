#ifndef RAYTRACEREXPERIMENT_EXAMPLESCENE_H
#define RAYTRACEREXPERIMENT_EXAMPLESCENE_H


#include <math.h>
#include "../src/geometries.h"
#include "../src/transform.h"

void generateRig(Scene *scene){

    Camera camera = {
            .origin={0, -5, 0},
            .direction={0, 0, 0},
    };

    // light on the top left side
    DirLight light = {.direction={0.2f, 0.6f, -0.2f}};

    scene->camera = camera;
    scene->light = light;
}


void generateExampleScene(Scene *scene){

    generateRig(scene);
    scene->isAnimated = true;
    scene->startFrame = 101;
    scene->endFrame = 103;

    parseObjFile(scene, "../examples/monkey.obj");

    float transformMatrix[9] = {
            0, 0, 0,
            0, 0, M_PI/4,
            1, 1, 1,
    };

    transformObject(&scene->object, transformMatrix);
}


#endif //RAYTRACEREXPERIMENT_EXAMPLESCENE_H
