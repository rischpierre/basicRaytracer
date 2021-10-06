#include <bits/types/clock_t.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>

#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"
#include "mathLib.h"
#include "transform.h"


Scene defineExampleScene() {

    // lets design a flat scene  along x, y
    // defining a triangle that is in the sight of the ray
    Face f1 = {.v0={2, 2, 0},
            .v1={2, -1, -2},
            .v2={2, -1, 2},
            .normal={-1, 0, 0}
    };

//    float v0[4] = {2, 2, 0, 1};
//    float v1[4] = {2, -1, -2, 1};
//    float v2[4] = {2, -1, 2, 1};


//    float transformMatrix[9] = {
//            0, 0, 0,            // translate
//            0, 0, 0,            // rotate in rads: M_PI/4
//            1.f, 1.f, 1.f       // scale
//    };
    // todo transform from 33 matrix to a 44 matrix in the matrix mult
//    transform(v0, transformMatrix);
//    transform(v1, transformMatrix);
//    transform(v2, transformMatrix);

    // todo need to recompute face normal after transformation
//    f1.normal = computeNormal(face);

//    for (uint8_t i = 0; i < 3; i++) {
//
//        f1.v0[i] = v0[i];
//        f1.v1[i] = v1[i];
//        f1.v2[i] = v2[i];
//    }

    Camera camera = {
            .focalPoint={0, 0, 0},
            .direction={10, 1, 0},
            .filmSize={6, 6}
    };

    // light on the right side
    DirLight light = {.direction={1, 0, 0}};

    Scene scene;
    scene.camera = camera;
    scene.face = f1;
    scene.light = light;

    return scene;
}

float computeColor(Face f, DirLight light) {

    float angle = angleBetweenVectors(light.direction, f.normal);

    return interpolation1d(angle, M_PI / 2, M_PI, 0, 1);
}


int main(int argc, char *argv[]) {

    const uint16_t resolutionY = 1000;
    const uint16_t resolutionX = 1000;

    Scene scene = defineExampleScene();

    // this is first a test with planar projection
    Ray ray = {.origin={0, 0, 0},
            .direction={1, 0, 0}};


    float **red = (float **) malloc(resolutionX * sizeof(float *));
    float **green = (float **) malloc(resolutionX * sizeof(float *));
    float **blue = (float **) malloc(resolutionX * sizeof(float *));
    for (uint16_t i = 0; i < resolutionX; i++) {
        red[i] = (float *) malloc(resolutionY * sizeof(float));
        blue[i] = (float *) malloc(resolutionY * sizeof(float));
        green[i] = (float *) malloc(resolutionY * sizeof(float));
    }


    // todo put the rayTrace algo in a function
    clock_t start = clock();

    for (uint16_t x = 0; x < resolutionX; x++) {
        for (uint16_t y = 0; y < resolutionY; y++) {

            // z becomes x in screen view
            ray.origin[2] = interpolation1d((float) x, 0, (float) resolutionX, scene.camera.filmSize[0] / 2,
                                            -scene.camera.filmSize[0] / 2);
            ray.origin[1] = interpolation1d((float) y, 0, (float) resolutionY, -scene.camera.filmSize[1] / 2,
                                            scene.camera.filmSize[1] / 2);

            bool intersected = isRayIntersectsTriangle(&ray, &scene.face);
            if (intersected) {
//                float color = computeColor(scene.face, scene.light);
                float color = 1.f;
                red[x][y] = color;
                green[x][y] = color;
                blue[x][y] = color;

            } else {
                red[x][y] = 0.f;
                green[x][y] = 0.f;
                blue[x][y] = 0.f;
            }
        }
    }


    clock_t end = clock();
    printf("render time: %f s\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
    char *imagePath = "render.bmp";
    writeBmpFile(resolutionX, resolutionY, red, green, blue, imagePath);

    printf("Wrote image : %s", imagePath);

    for (uint16_t i = 0; i < resolutionX; i++) {
        free(red[i]);
        free(green[i]);
        free(blue[i]);
    }

    free(red);
    free(green);
    free(blue);

    return 0;
}