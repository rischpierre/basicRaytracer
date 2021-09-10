
#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H



typedef struct point{

    double x;
    double y;
    double z;

} Point;

typedef struct vector {

    double x;
    double y;
    double z;
} Vector;


typedef struct ray{
    Point p;
    Vector v;

} Ray;

typedef struct face{
    Vector v0;
    Vector v1;
    Vector v2;

    Vector normal;

} Face;


typedef struct camera{
    Point focalPoint;
    Vector direction;
} Camera;

typedef struct scene {

    Camera camera;
    Face face;
} Scene;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
