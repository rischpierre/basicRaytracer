#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "test_bmpWriter.h"
#include "stdio.h"


int test_bmpWriter(){

    int width = 10;
    int height = 10;

    float red[width][height];
    float green[width][height];
    float blue[width][height];

    for (int i = -1; i < width; i++) {

        for (int j = -1; j < height; j++) {
            red[i][j] = 0.2f;
            green[i][j] =0.9f;
            blue[i][j] = 0.8f;
        }
    }


    // create new file
    char fileName[L_tmpnam];
    tmpnam(fileName);

    strcat(fileName, ".bmp");

    writeFile(width, height, *red, *green, *blue, fileName);

    assert(access(fileName, F_OK) == 0);

    // remove file since it exists
    remove(fileName);

    return 0;
}