
#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H



typedef struct vector {

    float x;
    float y;
    float z;
} Vector;


typedef struct ray{
    Vector origin;
    Vector direction;

} Ray;

typedef struct face{
    Vector v0;
    Vector v1;
    Vector v2;

    Vector normal;

} Face;


typedef struct camera{
    Vector focalPoint;
    Vector direction;
    float filmSizeX;
    float filmSizeY;

} Camera;

typedef struct dirLight{
    float direction[3];

} DirLight;


typedef struct scene {
    DirLight light;
    Camera camera;
    Face face;
} Scene;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
