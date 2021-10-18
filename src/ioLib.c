
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
    uint8_t bufferLength = 255;
    char buffer[bufferLength];

    Object object1;
//    scene.object = object1;

    // faces are in a linked list
    uint8_t vertexSize = 128;
    Face *firstFace = NULL;
    Face *currentFace = NULL;
    float vertices[vertexSize][3];
    char* vertexDelimiter = "v ";

    int line = 1;
    int objectNumber = 0;
    int vertexId = 0;
    while(fgets(buffer, bufferLength, file)){
        if (objectNumber > 1){
            printf("Only one object is supported yet");
            assert(false);
        }
        if (strncmp(buffer, "o ", 2) == 0){
            objectNumber++;
            printf("object n: %s", buffer);
        }
        else if (strncmp(buffer, "vn ", 2) == 0){
            printf("vertex n: %s", buffer);

        }else if (strncmp(buffer, vertexDelimiter, 2) == 0){
            char * token = strtok(buffer, "v ");
            int k = 0;
            while (token != NULL){
                vertices[vertexId][k] = (float)strtod(token, NULL);
                token = strtok(NULL, " ");
                k++;
            }
            vertexId++;

        }else if (strncmp(buffer, "f ", 2) == 0){
            char * token = strtok(buffer, "f ");
            int k = 0;
            while (token != NULL){
                Face face = {.normal={0, 0, 0}, .v0={vertices[vertexId][0]}, .v1={vertices[vertexId][1]}, .v2=vertices[vertexId][2]};
                if (currentFace != NULL){
                   currentFace->next = &face;
               }else{
                    currentFace = &face;
               }
                if (firstFace == NULL){
                    firstFace = &face;
                }
                token = strtok(NULL, " ");
                k++;
            }
            vertexId++;
        }
        line++;
    }

    fclose(file);
}
