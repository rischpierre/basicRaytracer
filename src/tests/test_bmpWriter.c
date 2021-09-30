
#include <string.h>
#include <unistd.h>
#include "stdio.h"
#include "../bmpWriter.h"

#include "criterion/criterion.h"

Test(bmp_writer, file_is_written_on_disk){

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

    cr_assert(access(fileName, F_OK) == 0);

    // remove file since it exists
    remove(fileName);

}