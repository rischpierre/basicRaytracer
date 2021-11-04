#ifndef RAYTRACEREXPERIMENT_RAYTRACER_H
#define RAYTRACEREXPERIMENT_RAYTRACER_H

#include "stdbool.h"
#include "geometries.h"

bool isRayIntersectsTriangle(const Ray *ray, const Face *face, float *distance);
float computeColor(const float *faceNormal, const DirLight* light);
void render(Scene *scene, char *imagePath);
void freeScene(Scene *scene);
void splitQuads(Object *o);
void *renderLoop(void* arguments);

// this is used to pass on args for multi-threaded functions
struct renderArgs{
    Scene *scene;
    float** red;
    float** green;
    float** blue;
    int start;
    int end;
    int threadId;
};

#endif //RAYTRACEREXPERIMENT_RAYTRACER_H
