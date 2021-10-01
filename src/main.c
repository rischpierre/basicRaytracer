#include <bits/types/clock_t.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>

#include "geometries.h"
#include "raytracer.h"
#include "bmpWriter.h"
#include "utils.h"
#include "vector.h"
#include "transform.h"



Scene defineExampleScene(){

    // lets design a flat scene  along x, y
    // defining a triangle that is in the sight of the ray
    Face f1;

    f1.normal.x = -1;
    f1.normal.y = 0;
    f1.normal.z = 0;


    float v0[4] = {2, 2, 0, 1};
    float v1[4] = {2, -1, -2, 1};
    float v2[4] = {2, -1, 2, 1};


    float transformMatrix[9] = {
            0, 0, 0,            // translate
            0, 0, 0,            // rotate in rads: M_PI/4
            1.f, 1.f, 1.f       // scale
    };

    transform(v0, transformMatrix);
    transform(v1, transformMatrix);
    transform(v2, transformMatrix);


    // todo need to recompute face normal after transformation
//    f1.normal = computeNormal(face);

    // todo use arrays to store the x, y, z coords.
    f1.v0.x = v0[0];
    f1.v0.y = v0[1];
    f1.v0.z = v0[2];

    f1.v1.x = v1[0];
    f1.v1.y = v1[1];
    f1.v1.z = v1[2];

    f1.v2.x = v2[0];
    f1.v2.y = v2[1];
    f1.v2.z = v2[2];


    Camera camera;

    camera.focalPoint.x = 0;
    camera.focalPoint.y = 0;
    camera.focalPoint.z = 0;

    camera.direction.x = 10;
    camera.direction.y = 1;
    camera.direction.z = 0;

    camera.filmSizeX = 6;
    camera.filmSizeY = 6;



    // light on the right side
    DirLight light;

    light.direction[0] = 1;
    light.direction[1] = 0;
    light.direction[2] = 0;

    Scene scene;
    scene.camera = camera;
    scene.face = f1;
    scene.light = light;

    return scene;
}

float computeColor(Face f, DirLight light) {

    Vector v1;
    v1.x = light.direction[0];
    v1.y = light.direction[1];
    v1.z = light.direction[2];
    float angle = angleBetweenVectors(&v1, &f.normal);

    return interpolation1d(angle, M_PI/2, M_PI, 0, 1);
}



int main(int argc, char *argv[]) {

    const uint16_t resolutionY = 1000;
    const uint16_t resolutionX = 1000;

    Scene scene = defineExampleScene();

    // this is first a test with planar projection
    Ray ray;
    ray.direction.x = 1;
    ray.direction.y = 0;
    ray.direction.z = 0;

    ray.origin.x = 0;


    float** red = (float**)malloc(resolutionX * sizeof(float*));
    float** green = (float**)malloc(resolutionX * sizeof(float*));
    float** blue = (float**)malloc(resolutionX * sizeof(float*));
    for (uint16_t i = 0; i < resolutionX; i++){
        red[i] = (float*)malloc(resolutionY * sizeof(float));
        blue[i] = (float*)malloc(resolutionY * sizeof(float));
        green[i] = (float*)malloc(resolutionY * sizeof(float));
    }


    // todo put the rayTrace algo in a function
    clock_t start = clock();

    for(uint16_t x = 0; x < resolutionX; x++) {
        for(uint16_t y = 0; y < resolutionY; y++) {

            ray.origin.z = interpolation1d((float)x, 0, (float)resolutionX, scene.camera.filmSizeX/2, - scene.camera.filmSizeX/2);
            ray.origin.y = interpolation1d((float)y, 0, (float)resolutionY, - scene.camera.filmSizeY/2, scene.camera.filmSizeY/2);

            bool intersected = isRayIntersectsTriangle( ray, scene.face);
            if (intersected) {
                float color = computeColor(scene.face, scene.light);
                red[x][y] = color;
                green[x][y] = color;
                blue[x][y] = color;

            } else{
                red[x][y] = 0.f;
                green[x][y] = 0.f;
                blue[x][y] = 0.f;
            }
        }
    }


    clock_t end = clock();
    printf("render time: %f s\n", (double)(end-start)/(double)CLOCKS_PER_SEC);
    char * imagePath = "render.bmp";
    writeFile(resolutionX, resolutionY, red, green, blue, imagePath);

    printf("Wrote image : %s", imagePath);

    for (uint16_t i=0; i< resolutionX; i++){
        free(red[i]);
        free(green[i]);
        free(blue[i]);
    }

    free(red);
    free(green);
    free(blue);

    return 0;
}