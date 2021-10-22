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
            .direction={10, 1, 0},
            .filmSize={6, 3.375f} // 16:9 ratio
    };

    // light on the right side
    DirLight light = {.direction={1, 0, 0}};

    Scene scene;
    scene.camera = camera;
    scene.light = light;

    return scene;
}

float computeColor(Face *f, DirLight light) {

    float angle = angleBetweenVectors(light.direction, f->normal);

    return interpolation1d(angle, M_PI / 2, M_PI, 0, 1);
}


int main(int argc, char *argv[]) {
    Scene scene = defineExampleScene();
    parseObjFile(&scene, "../examples/twoTriangle.obj");
    printFaces(scene.object.faces);
    exit(1);
//     test linked list here

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
            Face *currentFace;
            currentFace = scene.object.faces;
            while(currentFace != NULL) {
                bool intersected = isRayIntersectsTriangle(&ray, currentFace);
                if (intersected) {
                    float color = computeColor(scene.object.faces, scene.light);
                    red[x][y] = color;
                    green[x][y] = color;
                    blue[x][y] = color;

                } else {
                    red[x][y] = 0.f;
                    green[x][y] = 0.f;
                    blue[x][y] = 0.f;
                }
                currentFace = (Face *) currentFace->next;
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