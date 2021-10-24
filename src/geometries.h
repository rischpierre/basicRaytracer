
#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H


#include <stdbool.h>

typedef struct ray{
    float origin[3];
    float direction[3];

} Ray;

typedef struct face{
    float v0[3];
    float v1[3];
    float v2[3];
    float v3[3];

    bool isQuad;
    float normal[3];

} Face;

typedef struct obj{
   Face *faces;
   int faceNb;
   char* name;
}Object;

void printObject(const Object *o);

typedef struct camera{
    float focalPoint[3];
    float direction[3];

} Camera;

typedef struct dirLight{
    float direction[3];

} DirLight;


typedef struct scene {
    DirLight light;
    Camera camera;
    Object object;
} Scene;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
