#ifndef RAYTRACEREXPERIMENT_IOLIB_H
#define RAYTRACEREXPERIMENT_IOLIB_H
#include "geometries.h"


// the image origin is the bottom left corner
void writeBmpFile(int width, int height, float **red, float **green, float **blue, const char *filePath);
void parseObjFile(Scene *scene, const char *filePath);

#endif //RAYTRACEREXPERIMENT_IOLIB_H