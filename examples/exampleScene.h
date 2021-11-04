#ifndef RAYTRACEREXPERIMENT_EXAMPLESCENE_H
#define RAYTRACEREXPERIMENT_EXAMPLESCENE_H



#include "../src/geometries.h"

void generateRig(Scene *scene){

    Camera camera = {
            .focalPoint={3, 0, 0},
            .direction={-0.5f, 0.5f, 0},
    };

    // light on the top left side
    DirLight light = {.direction={0.2f, 0.6f, -0.2f}};

    scene->camera = camera;
    scene->light = light;
}


void generateExampleScene(Scene *scene){

    generateRig(scene);
    parseObjFile(scene, "monkey.obj");
    scene->isAnimated = true;
    scene->startFrame = 101;
    scene->endFrame = 103;
}


#endif //RAYTRACEREXPERIMENT_EXAMPLESCENE_H
