
#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H


#include <stdbool.h>

typedef struct {
    float origin[3];
    float direction[3];

} Ray;

typedef struct {
    float v0[3];
    float v1[3];
    float v2[3];
    float v3[3];

    bool isQuad;
    float n[3];

} Face;

typedef struct {
    Face *faces;
    int faceNb;
    char *name;
    float worldMatrix[16];
} Object;

void printObject(const Object *o, bool details);

typedef struct {
    float origin[3];
    float direction[3];

} Camera;

typedef struct {
    float direction[3];

} DirLight;


typedef struct {
    DirLight light;
    Camera camera;
    Object object;
    bool isAnimated;
    unsigned int startFrame;
    unsigned int endFrame;
} Scene;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
