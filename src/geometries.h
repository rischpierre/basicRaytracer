
#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H



typedef struct ray{
    float origin[3];
    float direction[3];

} Ray;

typedef struct face{
    float v0[3];
    float v1[3];
    float v2[3];

    float normal[3];

    // linked list of faces
    struct Face *next;

} Face;

typedef struct obj{
    // todo this needs to be a linked list
   Face f1;
}Object;


typedef struct camera{
    float focalPoint[3];
    float direction[3];
    float filmSize[2];

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
