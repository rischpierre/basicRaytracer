#include <bits/types/clock_t.h>
#include <time.h>
#include "geometries.h"
#include "raytracer.h"
#include "bmpWriter.h"
#include "utils.h"


Scene defineExampleScene(){

    // lets design a flat scene  along x, y
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
    f1.v1.z = -2;

    f1.v2.x = 2;
    f1.v2.y = -1;
    f1.v2.z = 2;

    Camera camera;

    camera.focalPoint.x = 0;
    camera.focalPoint.y = 0;
    camera.focalPoint.z = 0;

    camera.direction.x = 10;
    camera.direction.y = 1;
    camera.direction.z = 0;

    camera.filmSizeX = 6;
    camera.filmSizeY = 6;

    Scene scene;
    scene.camera = camera;
    scene.face = f1;

    return scene;
}


int main(int argc, char *argv[]) {

    float white = 0.8f;
    float black = 0.2f;

    // todo bug when increasing the resolution
    const int resolutionY = 500;
    const int resolutionX = 500;

    Scene scene = defineExampleScene();

    // this is first a test with planar projection
    Ray ray;
    ray.direction.x = 1;
    ray.direction.y = 0;
    ray.direction.z = 0;

    ray.origin.x = 0;

    float red[resolutionX][resolutionY];
    float green[resolutionX][resolutionY];
    float blue[resolutionX][resolutionY];

    // todo put the rayTrace algo in a function
    // todo print render time

    clock_t start = clock();

    for(int x = 0; x < resolutionX; x++) {
        for(int y = 0; y < resolutionY; y++) {

            ray.origin.z = interpolation1d((float)x, 0, (float)resolutionX, scene.camera.filmSizeX/2, - scene.camera.filmSizeX/2);
            ray.origin.y = interpolation1d((float)y, 0, (float)resolutionY, - scene.camera.filmSizeY/2, scene.camera.filmSizeY/2);

            bool intersected = isRayIntersectsTriangle( ray, scene.face);
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

    clock_t end = clock();
    printf("render time: %f s\n", (double)(end-start)/(double)CLOCKS_PER_SEC);

    writeFile(resolutionX, resolutionY, *red, *green, *blue, "render.bmp");

    return 0;
}