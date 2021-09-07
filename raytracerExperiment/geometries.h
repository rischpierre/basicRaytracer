//
// Created by pierre on 2021-09-07.
//

#ifndef RAYTRACEREXPERIMENT_GEOMETRIES_H
#define RAYTRACEREXPERIMENT_GEOMETRIES_H

typedef struct vertex{

    double x;
    double y;
    double z;

} Vertex;

typedef struct face{
    Vertex v0;
    Vertex v1;
    Vertex v2;

} Face;

#endif //RAYTRACEREXPERIMENT_GEOMETRIES_H
