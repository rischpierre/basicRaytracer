
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

#include "gtest/gtest.h"
#include <unistd.h>
#include "../src/ioLib.h"

TEST(splitFaceToken, valid_output) {
    int vertexId = -1;
    int vertexNId = -1;
    splitFaceToken("34/1/3", &vertexId, &vertexNId);
    ASSERT_EQ(vertexId, 33);
    ASSERT_EQ(vertexNId, 2);
}


TEST(parseVertices, valid_output){
    float vertices[2][3];
    const char *buffer = "v -0.174167 3.415299 0.296311";
    int vertexId = 0;
    parseVertices(*vertices, buffer, &vertexId);
    ASSERT_FLOAT_EQ(vertices[0][0], -0.174167);
    ASSERT_FLOAT_EQ(vertices[0][1], 3.415299);
    ASSERT_FLOAT_EQ(vertices[0][2], 0.296311);
}

TEST(parseFace, valid_output){
    float vertices[4][3] = {
            {1,  2,  3},
            {4,  5,  6},
            {7,  8,  9},
            {10, 11, 12}
    };
    float vertexNormals[2][3] = {
            {11, 22, 33},
            {12, 23, 34}
    };
    const char *buffer = "f 1/1/2 2/2/2 3/3/2 4/4/2";
    Face f = parseFace(buffer, *vertices, *vertexNormals);

    ASSERT_FLOAT_EQ(f.v0[0], 1);
    ASSERT_FLOAT_EQ(f.v1[0], 4);
    ASSERT_FLOAT_EQ(f.v1[2], 6);
    ASSERT_FLOAT_EQ(f.v1[2], 6);
    ASSERT_FLOAT_EQ(f.v3[2], 12);
    ASSERT_FLOAT_EQ(f.n[0], 12);
    ASSERT_FLOAT_EQ(f.n[1], 23);
    ASSERT_FLOAT_EQ(f.n[2], 34);
}


TEST(bmp_writer, file_is_written_on_disk){

    int resolutionX = 10;
    int resolutionY = 10;

    float** red = (float**)malloc(resolutionX * sizeof(float*));
    for (int i = 0; i < resolutionX; i++)
        red[i] = (float*)malloc(resolutionY * sizeof(float));


    float** green = (float**)malloc(resolutionX * sizeof(float*));
    for (int i = 0; i < resolutionX; i++)
        green[i] = (float*)malloc(resolutionY * sizeof(float));


    float** blue = (float**)malloc(resolutionX * sizeof(float*));
    for (int i = 0; i < resolutionX; i++)
        blue[i] = (float*)malloc(resolutionY * sizeof(float));

    for (int i = 0; i < resolutionX; i++) {

        for (int j = 0; j < resolutionY; j++) {
            red[i][j] = 0.2f;
            green[i][j] =0.9f;
            blue[i][j] = 0.8f;
        }
    }

    // create new file
    char fileName[L_tmpnam];
    tmpnam(fileName);

    strcat(fileName, ".bmp");

    writeBmpFile(resolutionX, resolutionY, red, green, blue, fileName);

    ASSERT_EQ(access(fileName, F_OK), 0);

    // remove file since it exists
    remove(fileName);

    for (int i = 0; i < resolutionX; i++) {
        free(red[i]);
        free(green[i]);
        free(blue[i]);
    }

    free(red);
    free(green);
    free(blue);
}