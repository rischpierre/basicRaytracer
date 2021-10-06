#ifndef RAYTRACEREXPERIMENT_IOLIB_H
#define RAYTRACEREXPERIMENT_IOLIB_H


void writeBmpFile(int width, int height, float **red, float **green, float **blue, const char *filePath);
void parseObjFile(char **lines, const char *filePath);

#endif //RAYTRACEREXPERIMENT_IOLIB_H