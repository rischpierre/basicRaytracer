
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


typedef struct vertex{

    double x;
    double y;
    double z;

} Vertex;


typedef struct ray{
    Point p;
    Vector v;

} Ray;

typedef struct face{
    Vertex v0;
    Vertex v1;
    Vertex v2;

} Face;


typedef struct camera{
    Point focalPoint;
    Vector v;
} Camera;


#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
