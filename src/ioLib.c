
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ioLib.h"
#include "geometries.h"


void writeBmpFile(int width, int height, float **red, float **green, float **blue, const char *filePath) {

    FILE *file;
    unsigned char *img = NULL;
    int filesize = 54 + 3 * width * height;

    img = (unsigned char *) malloc(3 * width * height);
    memset(img, 0, 3 * width * height);


    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            int r = (int)(red[i][j] * 255.f);
            int g = (int)(green[i][j] * 255.f);
            int b = (int)(blue[i][j] * 255.f);

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;

            int x = i;
            int y = (height - 1) - j;

            img[(x + y * width) * 3 + 2] = (unsigned char) (r);
            img[(x + y * width) * 3 + 1] = (unsigned char) (g);
            img[(x + y * width) * 3 + 0] = (unsigned char) (b);
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    bmpinfoheader[4] = (unsigned char) (width);
    bmpinfoheader[5] = (unsigned char) (width >> 8);
    bmpinfoheader[6] = (unsigned char) (width >> 16);
    bmpinfoheader[7] = (unsigned char) (width >> 24);
    bmpinfoheader[8] = (unsigned char) (height);
    bmpinfoheader[9] = (unsigned char) (height >> 8);
    bmpinfoheader[10] = (unsigned char) (height >> 16);
    bmpinfoheader[11] = (unsigned char) (height >> 24);

    file = fopen(filePath, "wb");
    fwrite(bmpfileheader, 1, 14, file);
    fwrite(bmpinfoheader, 1, 40, file);
    for (int i = 0; i < height; i++) {
        
        // write pixel data
        fwrite(img + (width * (height - i - 1) * 3), 3, width, file);
        
        // add padding at the end of each row
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, file);
    }

    free(img);
    fclose(file);
}

void splitFaceToken(const char* token, int *vertexId, int *vertexNId){
    char tmp[255];
    strcpy(tmp, token);
    char* found = strtok(tmp, "/");
    int i = 0;
    while (found != NULL){
        if (i == 0){
            *vertexId = (int)strtol(found, (char **)NULL, 10) - 1;
        }else if (i == 2){
            *vertexNId = (int)strtol(found, (char **)NULL, 10) - 1;
        }
        found = strtok(NULL, "/");
        i++;
    }
}

void parseVertices(float* vertices, const char* buffer, const int *vertexId){
    char tmpBuffer[BUFFER_SIZE];
    strcpy(tmpBuffer, buffer);
    char * token = strtok(tmpBuffer, TAG_VERTEX);
    int coordId = 0;
    while (token != NULL){
        *(vertices + *vertexId * 3 + coordId) = (float)strtod(token, NULL);
        token = strtok(NULL, " ");
        coordId++;
    }
}

Face parseFace(const char *buffer, const float *vertices, const float *vertexNormals) {

    char tmpBuffer[BUFFER_SIZE];
    strcpy(tmpBuffer, buffer);
    Face f;
    int faceGroupId = 0;
    char* token;
    char* rest = tmpBuffer;
    while ((token = strtok_r(rest, TAG_FACE, &rest))){
        int matchingVertexId = -1;
        int matchingVertexNId = -1;
        splitFaceToken(token, &matchingVertexId, &matchingVertexNId);
        if (matchingVertexNId == -1 || matchingVertexId == -1){
            printf("Unable to find the matching vertex ids");
            exit(1);
        }

        for (int i = 0; i < 3; i++){
            float vertexTmp = *(vertices + matchingVertexId * 3 + i);
            if (faceGroupId == 0){
                f.n[i] = *(vertexNormals + matchingVertexNId * 3 + i);
                f.v0[i] = vertexTmp;

            }else if(faceGroupId == 1){
                f.v1[i] = vertexTmp;

            }else if(faceGroupId == 2){
                f.v2[i] = vertexTmp;

            }else{
                f.v3[i] = vertexTmp;
                f.isQuad = true;
            }
        }
        faceGroupId++;
    }
    return f;
}

void parseObjFile(Scene *scene, const char *filePath){
    FILE *file;
    file = fopen(filePath, "r");

    if (file == NULL){
        printf("Unable to read the file: %s", filePath);
        exit(1);
    }

    char buffer[BUFFER_SIZE];

    // get the size of the objects, faces and vertices
    int objectNb = 0;
    int faceNb = 0;
    int vertexNb = 0;
    int vertexNNb = 0;
    while(fgets(buffer, BUFFER_SIZE, file)) {
        if (objectNb > 1) {
            printf("Only one object is supported yet");
            assert(false);
        }
        if (strncmp(buffer, TAG_OBJECT, strlen(TAG_OBJECT)) == 0){
            objectNb++;
        }else if (strncmp(buffer, TAG_FACE, strlen(TAG_FACE)) == 0){
           faceNb++;
        }else if (strncmp(buffer, TAG_VERTEX_N, strlen(TAG_VERTEX_N)) == 0){
            vertexNNb++;
        }else if (strncmp(buffer, TAG_VERTEX, strlen(TAG_VERTEX)) == 0){
            vertexNb++;
        }
    }

    float vertices[vertexNb][3];
    float vertexNormals[vertexNNb][3];
    Face *faces = (Face*)malloc(sizeof(Face) * faceNb);

    int line = 1;
    int vertexId = 0;
    int vertexNId = 0;
    int faceId = 0;
    char *name = malloc(sizeof(*name) * BUFFER_SIZE);

    rewind(file);
    while(fgets(buffer, BUFFER_SIZE, file)){
        // object name
        if (strncmp(buffer, TAG_OBJECT, strlen(TAG_OBJECT)) == 0) {
            char *token = strtok(buffer, " ");
            strncpy(name, &(token[2]), BUFFER_SIZE);

            // vertices
        }else if (strncmp(buffer, TAG_VERTEX, strlen(TAG_VERTEX)) == 0){
            parseVertices(*vertices, buffer, &vertexId);
            vertexId++;

            // vertex normal
        }else if (strncmp(buffer, TAG_VERTEX_N, strlen(TAG_VERTEX_N)) == 0) {
            char * token = strtok(buffer, TAG_VERTEX_N);
            int coordId = 0;
            while (token != NULL){
                vertexNormals[vertexNId][coordId] = (float)strtod(token, NULL);
                token = strtok(NULL, " ");
                coordId++;
            }
            vertexNId++;

            // faces
        }else if (strncmp(buffer, TAG_FACE, strlen(TAG_FACE)) == 0){
            Face f = parseFace(buffer, *vertices, *vertexNormals);
            faces[faceId] = f;
            faceId++;
        }
        line++;
    }
    scene->object.name = name;
    scene->object.faces = faces;
    scene->object.faceNb = faceNb;
    fclose(file);
}
