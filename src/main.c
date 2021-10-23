#include <bits/types/clock_t.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>

#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"
#include "mathLib.h"


Scene defineExampleScene() {

    Camera camera = {
            .focalPoint={0, 0, 0},
            .direction={1, 0, 0},
            .filmSize={6, 3.375f} // 16:9 ratio
    };

    // light on the right side
    DirLight light = {.direction={1, 0, 0}};

    Scene scene;
    scene.camera = camera;
    scene.light = light;

    return scene;
}

int main(int argc, char *argv[]) {
    Scene scene = defineExampleScene();
    parseObjFile(&scene, "../examples/triangle.obj");
    exit(1);

    const uint16_t resolutionY = 720;
    const uint16_t resolutionX = 1280;

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
            // world: y -> screen: x
            // world: z -> screen: y
            ray.origin[1] = interpolation1d((float) x, 0, (float) resolutionX, scene.camera.filmSize[0] / 2,
                                            -scene.camera.filmSize[0] / 2);

            ray.origin[2] = interpolation1d((float) y, 0, (float) resolutionY, -scene.camera.filmSize[1] / 2,
                                            scene.camera.filmSize[1] / 2);

            for (int i = 0; i < scene.object.faceNb; i++){
                Face* currentFace = &scene.object.faces[i];
                // todo bug here with face normal and intersection, make the example in the unittests
                bool intersected = isRayIntersectsTriangle(&ray, currentFace);
                if (intersected) {
                    // todo unable to compute the valid color when face normal is half pointing
                    float color = computeColor(currentFace->normal, &scene.light);
                    red[x][y] = color;
                    green[x][y] = color;
                    blue[x][y] = color;
                    break;

                } else {
                    red[x][y] = 0.f;
                    green[x][y] = 0.f;
                    blue[x][y] = 0.f;
                }
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