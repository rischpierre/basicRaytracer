
#include "gtest/gtest.h"

#include <unistd.h>
#include "../src/bmpWriter.h"



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

}