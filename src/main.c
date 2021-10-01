#include <bits/types/clock_t.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include "geometries.h"
#include "raytracer.h"
#include "bmpWriter.h"
#include "utils.h"
#include "vector.h"

Scene defineExampleScene(){

    // lets design a flat scene  along x, y
    // defining a triangle that is in the sight of the ray
    Face f1;

    f1.normal.x = -1;
    f1.normal.y = 0;
    f1.normal.z = 0;

    // todo create 66 a transform matrix input
    // define transform
    float tx = 0;
    float ty = 0;
    float tz = 0;

    // in radians
    float rx = 0;
    float ry = 0;
    float rz = 0;
//    float rz = M_PI/4;

    float sx = 1.f;
    float sy = 1.f;
    float sz = 1.f;

    // todo put the transform matricies in functions
    float scaleMatrix[16] = {
            sx, 0, 0, 0,
            0, sy,  0, 0,
            0, 0, sz, 0,
            0 , 0 , 0 ,1
    };

    float rxMatrix[16] = {
            1, 0, 0, 0,
            0, cosf(rx),  -sinf(rx) , 0,
            0, sinf(rx), cosf(rx), 0,
            0 , 0 , 0 ,1
    };

    float ryMatrix[16] = {
            cosf(ry), 0, sinf(ry), 0,
            0, 1,  0, 0,
            -sinf(ry), 0, cosf(ry), 0,
            0 , 0 , 0 , 1
    };

    float rzMatrix[16] = {
            cosf(rz), -sinf(rz), 0, 0,
            sinf(rz), cosf(rz), 0, 0,
            0, 0, 1, 0,
            0 , 0 , 0 , 1
    };

    // translate everything to the -z


    float matrix44fTranslate[16]= {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            tx, ty, tz, 1
    };

    float v0[4] = {2, 2, 0, 1};
    float v1[4] = {2, -1, -2, 1};
    float v2[4] = {2, -1, 2, 1};

    // matrix order SRT
    multVectMatrix44(v0, scaleMatrix);
    multVectMatrix44(v1, scaleMatrix);
    multVectMatrix44(v2, scaleMatrix);

    // rotate along x
    multVectMatrix44(v0, rxMatrix);
    multVectMatrix44(v1, rxMatrix);
    multVectMatrix44(v2, rxMatrix);

    // rotate along y
    multVectMatrix44(v0, ryMatrix);
    multVectMatrix44(v1, ryMatrix);
    multVectMatrix44(v2, ryMatrix);

    // rotate along z
    multVectMatrix44(v0, rzMatrix);
    multVectMatrix44(v1, rzMatrix);
    multVectMatrix44(v2, rzMatrix);

    // translate
    multVectMatrix44(v0, matrix44fTranslate);
    multVectMatrix44(v1, matrix44fTranslate);
    multVectMatrix44(v2, matrix44fTranslate);

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

    const int resolutionY = 1000;
    const int resolutionX = 1000;

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
    for (int i = 0; i < resolutionX; i++){
        red[i] = (float*)malloc(resolutionY * sizeof(float));
        blue[i] = (float*)malloc(resolutionY * sizeof(float));
        green[i] = (float*)malloc(resolutionY * sizeof(float));
    }


    // todo put the rayTrace algo in a function
    clock_t start = clock();

    for(int x = 0; x < resolutionX; x++) {
        for(int y = 0; y < resolutionY; y++) {

            ray.origin.z = interpolation1d((float)x, 0, (float)resolutionX, scene.camera.filmSizeX/2, - scene.camera.filmSizeX/2);
            ray.origin.y = interpolation1d((float)y, 0, (float)resolutionY, - scene.camera.filmSizeY/2, scene.camera.filmSizeY/2);

            // todo change the color based on the direction of the light

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

    for (int i=0; i< resolutionX; i++){
        free(red[i]);
        free(green[i]);
        free(blue[i]);
    }

    free(red);
    free(green);
    free(blue);

    return 0;
}