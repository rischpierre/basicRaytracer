#include "geometries.h"
#include "raytracer.h"
#include "bmpWriter.h"

#define BYTES_PER_PIXEL 3

// todo first start make a 2d projection of the created face, need to

Scene defineScene(){

    // lets design a flat scene  along x, y

    Face f1;

    f1.v0.x = 10;
    f1.v0.y = 0;
    f1.v0.z = 0;

    f1.v1.x = 10;
    f1.v1.y = 1;
    f1.v1.z = 0;

    f1.v2.x = 10;
    f1.v2.y = 0;
    f1.v2.z = 1;

    Camera camera;

    camera.focalPoint.x = 0;
    camera.focalPoint.y = 0;
    camera.focalPoint.z = 0;

    camera.direction.x = 10;
    camera.direction.y = 1;
    camera.direction.z = 0;

    Scene scene;
    scene.camera = camera;
    scene.face = f1;

    return scene;
}


int main(int argc, char *argv[]) {


    //todo put this in a unit test
//    int width = 200;
//    int height = 200;
//
//    float red[width][height];
//    float green[width][height];
//    float blue[width][height];
//
//    for (int i = 0; i < width; i++) {
//
//        for (int j = 0; j < height; j++) {
//            red[i][j] = 0.2f;
//            green[i][j] =0.9f;
//            blue[i][j] = 0.8f;
//        }
//    }
//
//    writeFile(width, height, *red, *green, *blue, "render.bmp");

    float white = 0.8f;
    float black = 0.2f;

    const int resolutionY = 10;
    const int resolutionX = 10;

    //  todo geometries
//    Scene scene = defineScene();

    float filmSizeX = 6;
    float filmSizeY = 6;
    float pixelIncrementX = filmSizeX / (float)resolutionY;
    float pixelIncrementY = filmSizeY / (float)resolutionX;

    // defining a triangle that is in the sight of the ray
    Face f1;

    f1.normal.x = -1;
    f1.normal.y = 0;
    f1.normal.z = 0;

    f1.v0.x = 2;
    f1.v0.y = 2;
    f1.v0.z = 0;

    f1.v1.x = 2;
    f1.v1.y = -1;
    f1.v1.z = -1;

    f1.v2.x = 2;
    f1.v2.y = -1;
    f1.v2.z = 1;


    // this is first a test with planar projection
    Ray ray;
    ray.direction.x = 1;
    ray.direction.y = 0;
    ray.direction.z = 0;


    float red[resolutionX][resolutionY];
    float green[resolutionX][resolutionY];
    float blue[resolutionX][resolutionY];

    for(int x = 0; x < resolutionX; x++) {
        for(int y = 0; y < resolutionY; y++) {

            red[x][y] = white;
            green[x][y] = white;
            blue[x][y] = white;

            ray.origin.x = (float)x + pixelIncrementX - filmSizeX/2;
            ray.origin.y = (float)y + pixelIncrementY - filmSizeY/2;

            bool intersected = isRayIntersectsTriangle( ray, f1);
            if (intersected) {
                red[x][y] = white;
                green[x][y] = white;
                blue[x][y] = white;

            } else{
                red[x][y] = black;
                green[x][y] = black;
                blue[x][y] = black;
            }
        }
    }

    writeFile(resolutionX, resolutionY, *red, *green, *blue, "render.bmp");

    return 0;
}