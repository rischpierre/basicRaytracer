
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


void parseObjFile(Scene *scene, const char *filePath){
    FILE *file;
    file = fopen(filePath, "r");

    if (file == NULL){
        printf("Unable to read the file: %s", filePath);
        exit(1);
    }

    int bufferLength = 255;

    char* vertexDelimiter = "v ";
    char* vertexNormalDelimiter = "vn ";
    char* faceDelimiter = "f ";
    char* objectDelimiter = "o ";

    char buffer[bufferLength];

    // get the size of the objects, faces and vertices
    int objectNb = 0;
    int faceNb = 0;
    int vertexNb = 0;
    int vertexNNb = 0;
    while(fgets(buffer, bufferLength, file)) {
        if (objectNb > 1) {
            printf("Only one object is supported yet");
            assert(false);
        }
        if (strncmp(buffer, objectDelimiter, strlen(objectDelimiter)) == 0){
            objectNb++;
        }else if (strncmp(buffer, faceDelimiter, strlen(faceDelimiter)) == 0){
           faceNb++;
        }else if (strncmp(buffer, vertexNormalDelimiter, strlen(vertexNormalDelimiter)) == 0){
            vertexNNb++;
        }else if (strncmp(buffer, vertexDelimiter, strlen(vertexDelimiter)) == 0){
            vertexNb++;
        }
    }

    float vertices[vertexNb][3];
    float vertexNormals[vertexNNb][3];
    Face faces[faceNb];

    int line = 1;
    int vertexId = 0;
    int vertexNId = 0;
    int faceId = 0;
    char *name = malloc(sizeof(char ) * bufferLength);
    Face current;
    rewind(file);
    while(fgets(buffer, bufferLength, file)){
        // object name
        if (strncmp(buffer, objectDelimiter, strlen(objectDelimiter)) == 0) {
            char *token = strtok(buffer, " ");
            // todo remove \n on the name of the object
            strncpy(name, &(token[2]), bufferLength);

            // vertices
        }else if (strncmp(buffer, vertexDelimiter, strlen(vertexDelimiter)) == 0){
            char * token = strtok(buffer, vertexDelimiter);
            int coordId = 0;
            while (token != NULL){
                vertices[vertexId][coordId] = (float)strtod(token, NULL);
                token = strtok(NULL, " ");
                coordId++;
            }
            vertexId++;

            // vertex normal
        }else if (strncmp(buffer, vertexNormalDelimiter, strlen(vertexNormalDelimiter)) == 0) {
            char * token = strtok(buffer, vertexNormalDelimiter);
            int coordId = 0;
            while (token != NULL){
                vertexNormals[vertexNId][coordId] = (float)strtod(token, NULL);
                token = strtok(NULL, " ");
                coordId++;
            }
            vertexNId++;

            // faces
        }else if (strncmp(buffer, faceDelimiter, strlen(faceDelimiter)) == 0){

            char * token = strtok(buffer, faceDelimiter);
            int faceGroupId = 0;
            while (token != NULL){
                // token[0] is the vertex id , token[2] is the vertexN (1/1/1)
                int matchingVertexId = (int)strtol(&token[0], (char **)NULL, 10) - 1;
                int matchingVertexNId = (int)strtol(&token[4], (char **)NULL, 10) - 1;

                for (int i = 0; i < 4; i++){

                    if (faceGroupId == 0){
                        float n = vertexNormals[matchingVertexNId][i];
                        if (n == 0) (n = 0); // to avoid having -0
                        current.normal[i] = n;
                        current.v0[i] = vertices[matchingVertexId][i];

                    }else if(faceGroupId == 1){
                        current.v1[i] = vertices[matchingVertexId][i];
                    }else if(faceGroupId == 2){
                        current.v2[i] = vertices[matchingVertexId][i];
                    }else{
                        current.v3[i] = vertices[matchingVertexId][i];
                        current.isQuad = true;
                    }
                }

                token = strtok(NULL, " ");
                faceGroupId++;
            }
            faces[faceId] = current;
            faceId++;
        }
        line++;
    }

    scene->object.name = name;
    scene->object.faces = faces;
    scene->object.faceNb = faceNb;

    fclose(file);
}
