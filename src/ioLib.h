#ifndef RAYTRACEREXPERIMENT_IOLIB_H
#define RAYTRACEREXPERIMENT_IOLIB_H
#include "geometries.h"

#define TAG_VERTEX "v "
#define TAG_VERTEX_N "vn "
#define TAG_FACE "f "
#define TAG_OBJECT "o "
#define BUFFER_SIZE 256

// the image origin is the bottom left corner
void writeBmpFile(int width, int height, float **red, float **green, float **blue, const char *filePath);
void parseObjFile(Scene *scene, const char *filePath);
void splitFaceToken(const char* token, int *vertexId, int *vertexNId);
void parseVertices(float* vertices, const char* buffer, const int *vertexId);
void parseFaces(Face* faces, const char* buffer, const int *faceId, const float* vertices, const float* vertexNormals);

#endif //RAYTRACEREXPERIMENT_IOLIB_H