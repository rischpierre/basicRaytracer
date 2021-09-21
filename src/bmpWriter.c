
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "bmpWriter.h"


void writeFile(const int width, const int height) {

    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3 * width * height;  //w is your image width, h is image height, both int

    img = (unsigned char *) malloc(3 * width * height);
    memset(img, 0, 3 * width * height);

    // todo this is a test, need to pass as args
    float red[2][2] = {{0.2f, 0.2f}, {0.2f, 0.2f}};
    float green[2][2] = {{0.2f, 0.2f}, {0.2f, 0.2f}};
    float blue[2][2] = {{0.2f, 0.2f}, {0.2f, 0.2f}};


    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int x = i;
            int y = (height - 1) - j;
            int r = (int) (red[i][j] * 255.f);
            int g = (int) (green[i][j] * 255.f);
            int b = (int) (blue[i][j] * 255.f);
            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
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

    f = fopen("img.bmp", "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for (int i = 0; i < height; i++) {
        
        // write pixel data
        fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
        
        // add padding at the end of each row
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
    }

    free(img);
    fclose(f);
}