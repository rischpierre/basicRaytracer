

/*
 *
 * Copyright (c) 2021 Pierre Risch
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of basicRaytracer.
 *
 * Author:          Pierre Risch <rischpierre@gmail.com>
 *
 */

#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "sceneEntities.h"
#include "sceneParser.h"
#include "raytracer.h"
#include "mathLib.h"


/*
 * Find the corresponding vertexId and vertexNId from a given face token.
 *
 * token: Face token to parse. i.e. `1/3/4`
 * vertexId: Found ID of the face token's vertex.
 * vertexId: Found ID of the face token's vertex normal.
 */
void getVerticesIndices(const char *token, int *vertexId, int *vertexNId) {
    char tmp[255];
    strcpy(tmp, token);
    char *found = strtok(tmp, "/");
    int i = 0;
    while (found != NULL) {
        if (i == 0) {
            *vertexId = (int) strtol(found, (char **) NULL, 10) - 1;
        } else if (i == 2) {
            *vertexNId = (int) strtol(found, (char **) NULL, 10) - 1;
        }
        found = strtok(NULL, "/");
        i++;
    }
}

/*
 * Parse the vertices from a line buffer in the obj file.
 *
 * vertices: The parsed vertices are added to this array.
 * buffer: Line to parse. i.e. `v 1.324 1.2352 4.23525`
 * vertexId: ID to increment when a line is parsed
 */
void parseVertices(float *vertices, const char *buffer, const int *vertexId) {
    char tmpBuffer[BUFFER_SIZE];
    strcpy(tmpBuffer, buffer);
    char *token = strtok(tmpBuffer, TAG_VERTEX);
    int coordId = 0;
    while (token != NULL) {
        *(vertices + *vertexId * 3 + coordId) = (float) strtod(token, NULL);
        token = strtok(NULL, " ");
        coordId++;
    }
}

/*
 * Parse the faces from a line buffer in the obj file.
 *
 * vertices: The parsed vertices are added to this array.
 * vertexNormals: The parsed vertex normals are added to this array.
 * buffer: Line to parse. i.e. `f 1/2/3 2/4/5 2/3/4`
 * vertexId: ID to increment when a line is parsed
 * return: Newly created face.
 */
Face parseFace(const char *buffer, const float *vertices, const float *vertexNormals) {

    char tmpBuffer[BUFFER_SIZE];
    strcpy(tmpBuffer, buffer);
    Face f = {.isQuad=false};
    int faceGroupId = 0;
    char *token;
    char *rest = tmpBuffer;
    while ((token = strtok_r(rest, TAG_FACE, &rest))) {
        int matchingVertexId = -1;
        int matchingVertexNId = -1;
        getVerticesIndices(token, &matchingVertexId, &matchingVertexNId);
        if (matchingVertexNId == -1 || matchingVertexId == -1) {
            printf("Unable to find the matching vertex ids");
            exit(1);
        }

        for (int i = 0; i < 3; i++) {
            float vertexTmp = *(vertices + matchingVertexId * 3 + i);
            if (faceGroupId == 0) {
                f.n[i] = *(vertexNormals + matchingVertexNId * 3 + i);
                f.v0[i] = vertexTmp;

            } else if (faceGroupId == 1) {
                f.v1[i] = vertexTmp;

            } else if (faceGroupId == 2) {
                f.v2[i] = vertexTmp;

            } else {
                f.v3[i] = vertexTmp;
                f.isQuad = true;
            }
        }
        faceGroupId++;
    }
    return f;
}

/*
 * Parse an object from an .obj file.
 * The object is then linked to the given scene struct.
 * It goes through all the lines in the obj file and parse the object components like
 * vertices, faces, faceNormals, etc...
 *
 * scene: Scene struct that contain the object to create.
 * filePath: Path of the obj file to parse.
 */
void parseObjFile(Scene *scene, const char *filePath) {
    FILE *file;
    file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Unable to read the file: %s", filePath);
        exit(1);
    }

    char buffer[BUFFER_SIZE];

    // get the size of the objects, faces and vertices
    int objectNb = 0;
    int faceNb = 0;
    int vertexNb = 0;
    int vertexNNb = 0;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        if (objectNb > 1) {
            printf("Only one object is supported yet");
            assert(false);
        }
        if (strncmp(buffer, TAG_OBJECT, strlen(TAG_OBJECT)) == 0) {
            objectNb++;
        } else if (strncmp(buffer, TAG_FACE, strlen(TAG_FACE)) == 0) {
            faceNb++;
        } else if (strncmp(buffer, TAG_VERTEX_N, strlen(TAG_VERTEX_N)) == 0) {
            vertexNNb++;
        } else if (strncmp(buffer, TAG_VERTEX, strlen(TAG_VERTEX)) == 0) {
            vertexNb++;
        }
    }

    float vertices[vertexNb][3];
    float vertexNormals[vertexNNb][3];
    Face *faces = (Face *) malloc(sizeof(Face) * faceNb);

    int line = 1;
    int vertexId = 0;
    int vertexNId = 0;
    int faceId = 0;
    char *name = (char *) malloc(sizeof(*name) * BUFFER_SIZE);

    rewind(file);
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // object name
        if (strncmp(buffer, TAG_OBJECT, strlen(TAG_OBJECT)) == 0) {
            char *token = strtok(buffer, " ");
            strncpy(name, &(token[2]), BUFFER_SIZE);

            // vertices
        } else if (strncmp(buffer, TAG_VERTEX, strlen(TAG_VERTEX)) == 0) {
            parseVertices(*vertices, buffer, &vertexId);
            vertexId++;

            // vertex normal
        } else if (strncmp(buffer, TAG_VERTEX_N, strlen(TAG_VERTEX_N)) == 0) {
            char *token = strtok(buffer, TAG_VERTEX_N);
            int coordId = 0;
            while (token != NULL) {
                vertexNormals[vertexNId][coordId] = (float) strtod(token, NULL);
                token = strtok(NULL, " ");
                coordId++;
            }
            vertexNId++;

            // faces
        } else if (strncmp(buffer, TAG_FACE, strlen(TAG_FACE)) == 0) {
            Face f = parseFace(buffer, *vertices, *vertexNormals);
            faces[faceId] = f;
            faceId++;
        }
        line++;
    }
    scene->object.name = name;
    scene->object.faces = faces;
    scene->object.faceNb = faceNb;

    // define object's default world matrix
    // todo put this elsewhere, maybe an obj initializer?
    generateIdentityMat44(scene->object.worldMatrix);

    splitQuads(&scene->object);

    // define color object here, in the future get info from mtl file
    scene->object.color[0] = 1.0f;
    scene->object.color[1] = 0.9f;
    scene->object.color[2] = 0.85f;

    fclose(file);
}
