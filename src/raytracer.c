#include <math.h>
#include <bits/types/clock_t.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>

#include "raytracer.h"
#include "mathLib.h"
#include "renderSettings.h"
#include "ioLib.h"
#include "transform.h"


bool isRayIntersectsTriangle(const Ray *ray, const Face *face, float *distance) {

    float edge1[3], edge2[3], p[3], q[3], t[3];
    float det, u, v, invertedDet;

    // find the two edges arround V0
    subVectors(edge1, face->v1, face->v0, 3);
    subVectors(edge2, face->v2, face->v0, 3);

    //  get p
    crossProduct(p, ray->direction, edge2);

    det = dotProduct(edge1, p);
    if (det > -RAY_TRACING_THRESHOLD && det < RAY_TRACING_THRESHOLD)
        return false;

    // precompute the inverse of the determinant
    invertedDet = 1.f / det;

    // distance from V to ray origin
    subVectors(t, ray->origin, face->v0, 3);

    // calculate u param
    u = dotProduct(t, p) * invertedDet;
    if (u < 0 || u > 1.f)  // the hit point is outside of the triangle
        return false;

    // calculate v param
    crossProduct(q, t, edge1);
    v = dotProduct(ray->direction, q) * invertedDet;
    if ( v < 0 || u + v > 1.f)  // hit point outside triangle
        return false;

    *distance = dotProduct(edge2, q) * invertedDet;

    return true;
}


float computeColor(const float *faceNormal, const DirLight *light) {
    float angle = angleBetweenVectors(light->direction, faceNormal);
    float result = interpolation1d(angle, M_PI / 2, M_PI, 0, 1);
    if (result < 0){
        return AMBIENT_CONTRIBUTION;
    }
    return result;
}

void splitQuads(Object *o) {
    int quadNb = 0;
    for(int fId = 0; fId < o->faceNb; fId++){
        Face current = o->faces[fId];
        if (current.isQuad){
            quadNb++;
        }
    }
    if (quadNb == 0) return;
    int newFaceNb =  (o->faceNb - quadNb) + 2 * quadNb;
    o->faces = (Face *)realloc(o->faces, sizeof(Face) * newFaceNb);
int newFaceId = o->faceNb; for(int currentFaceId = 0; currentFaceId < o->faceNb; currentFaceId++) {
        Face c = o->faces[currentFaceId];
        if (c.isQuad) {
            Face f;
            for (int i = 0; i < 3; i++) {
                f.v0[i] = c.v0[i];
                f.v1[i] = c.v2[i];
                f.v2[i] = c.v3[i];
                f.n[i] = c.n[i];
                f.isQuad = false;
            }
            o->faces[newFaceId] = f;
            newFaceId++;
        }
    }
    o->faceNb = newFaceNb;
}

struct args{

    Scene *scene;
    float** red;
    float** green;
    float** blue;
    int start;
    int end;
    int threadId;
};


void *renderLoop(void* arguments){

    Ray ray = {.origin={0, 0, 0},
            .direction={0, CAM_FOCAL_LENGTH, 0}};

    struct args *args = arguments;
    printf("Starting thread: %d\n", args->threadId);

//    int printIncrement = RESOLUTION_H / 10;
    // scanline process from top left to bottom right

//    printf("0 %%");
    for (int y = args->start; y < args->end; y++) {

        // log progress
//        if (y % printIncrement == 0){
//            int percent = ((RESOLUTION_H - y) * 100)/RESOLUTION_H;
//            printf("\r%d %%", percent);
//            fflush(stdout);
//        }

        for (int x = 0; x < RESOLUTION_W; x++) {

            // world: x -> screen: x
            // world: z -> screen: y
            ray.direction[0] = interpolation1d((float) x, 0, (float) RESOLUTION_W, -CAM_FILM_SIZE_W / 2,
                                               CAM_FILM_SIZE_W / 2);

            ray.direction[2] = interpolation1d((float) y, 0, (float) RESOLUTION_H, -CAM_FILM_SIZE_H / 2,
                                               CAM_FILM_SIZE_H / 2);

            float distance = WORLD_MAX_DISTANCE;
            float maxDistance = WORLD_MAX_DISTANCE;
            Face *nearestFace = NULL;

            for (int i = 0; i < args->scene->object.faceNb; i++) {

                Face *currentFace = &args->scene->object.faces[i];

                bool intersected = isRayIntersectsTriangle(&ray, currentFace, &distance);
                if (!intersected) {
                    continue;
                }

                if (distance < maxDistance) {
                    maxDistance = distance;
                    nearestFace = currentFace;
                }
            }

            if (nearestFace == NULL) {
                args->red[y][x] = 0;
                args->green[y][x] = 0;
                args->blue[y][x] = 0;
            }else {
                float color = computeColor(nearestFace->n, &args->scene->light);

                args->red[y][x] = color;
                args->green[y][x] = color;
                args->blue[y][x] = color;

            }
        }
    }
    printf("finish thread %d\n", args->threadId);

}

void render(Scene *scene){
    // this is first a test with planar projection



    float **red = (float **) malloc(RESOLUTION_H * sizeof(float *));
    float **green = (float **) malloc(RESOLUTION_H * sizeof(float *));
    float **blue = (float **) malloc(RESOLUTION_H * sizeof(float *));
    for (int i = 0; i < RESOLUTION_H; i++) {
        red[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
        green[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
        blue[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
    }

    // todo clock does not work in multithreading???

    clock_t startTime = clock();

    int threadCount = 8;
    pthread_t threads[threadCount];

    int start = 0;
    int lineIncrement = RESOLUTION_H/threadCount;
    struct args arguments[threadCount];

    for (int i = 0; i < threadCount; ++i) {
        pthread_t t;

        struct args args1 = {.scene=scene, .red=red, .green=green, .blue=blue, .start=start, .end=start+lineIncrement, .threadId=i};
        arguments[i] = args1;

        pthread_create(&t, NULL, &renderLoop, (void*)&arguments[i]);
        threads[i] = t;
        start += lineIncrement;
    }

    for (int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
    }


    clock_t end = clock();
    printf("\nrender time: %f s\n", (double) (end - startTime) / (double) CLOCKS_PER_SEC);
    char *imagePath = "render.bmp";

    writeBmpFile(RESOLUTION_W, RESOLUTION_H, red, green, blue, imagePath);

    printf("Wrote image : %s\n", imagePath);

    for (int i = 0; i < RESOLUTION_H; i++) {
        free(red[i]);
        free(green[i]);
        free(blue[i]);
    }

    free(red);
    free(green);
    free(blue);

}

void freeScene(Scene *scene) {
    free(scene->object.faces);
    free(scene->object.name);
    free(scene);
}
