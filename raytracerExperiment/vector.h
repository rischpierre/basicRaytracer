//
// Created by pierre on 2021-09-06.
//

#ifndef RAYTRACEREXPERIMENT_VECTOR_H
#define RAYTRACEREXPERIMENT_VECTOR_H
struct Vector {

    double x;
    double y;
    double z;
};

struct Vector crossProduct(struct Vector v1, struct Vector v2);

#endif //RAYTRACEREXPERIMENT_VECTOR_H
