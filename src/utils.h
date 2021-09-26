
#ifndef RAYTRACEREXPERIMENT_UTILS_H
#define RAYTRACEREXPERIMENT_UTILS_H

#include "stdbool.h"
#include "stdio.h"

void print_result(const bool success, const char *function);
float interpolation1d(float x, float x1, float x2, float y1, float y2);

#endif //RAYTRACEREXPERIMENT_UTILS_H
