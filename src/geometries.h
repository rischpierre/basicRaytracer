
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
} Camera;

typedef struct scene {

    Camera camera;
    Face face;
} Scene;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
