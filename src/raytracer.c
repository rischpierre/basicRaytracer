
/*
 *
 * Copyright (c) 2021 Pierre Risch
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of basicRaytracer.
 *
 * Author:          Pierre Risch <rischpierre@gmail.com>
 *
 */

#include <math.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>

#include "raytracer.h"
#include "mathLib.h"
#include "renderSettings.h"
#include "ioLib.h"
#include "transform.h"

/*
 * Check if a ray hits a given triangle. This is the implementation of the Möller-Trumbore algorithm
 *
 * ray: The ray that intersects or not the face.
 * face: The face that is intersected or not by the ray.
 * distance: The distance between the origin of the ray and the point of
 * intersection between the ray and the face.
 * return: true if the ray intersect the face.
 */
bool isRayIntersectsTriangle(const Ray *ray, const Face *face, float *distance) {

    float edge1[3], edge2[3], p[3], q[3], t[3];
    float det, u, v, invertedDet;

    // find the two edges around V0
    subVec3(edge1, face->v1, face->v0);
    subVec3(edge2, face->v2, face->v0);

    //  get p
    crossProductVec3(p, ray->direction, edge2);

    det = dotProductVec3(edge1, p);
    if (det > -RAY_TRACING_THRESHOLD && det < RAY_TRACING_THRESHOLD)
        return false;

    // precompute the inverse of the determinant
    invertedDet = 1.f / det;

    // distance from V to ray origin
    subVec3(t, ray->origin, face->v0);

    // calculate u param
    u = dotProductVec3(t, p) * invertedDet;
    if (u < 0 || u > 1.f)  // the hit point is outside the triangle
        return false;

    // calculate v param
    crossProductVec3(q, t, edge1);
    v = dotProductVec3(ray->direction, q) * invertedDet;
    if (v < 0 || u + v > 1.f)  // hit point outside triangle
        return false;

    *distance = dotProductVec3(edge2, q) * invertedDet;

    return true;
}

/*
 * Compute the color that radiates out of the face.
 * This function is oversimplified, It's a basic interpolation between the direction of the ray and the
 * direction of the light.
 * The more the face aligns with the light, the more light is coming from it.
 *
 * color: The resulting color.
 * faceNormal: The normal of the face being computed.
 * light: The directional light used to compute the color.
 * objectColor: RGB contribution multiplier.
 */
void computeColor(float color[3], const float *faceNormal, const DirLight *light, const float objectColor[3]) {
    float angle = angleBetweenVec3(light->direction, faceNormal);
    float result = interpolation1d(angle, M_PI / 2, M_PI, 0, 1);

    if (result < 0) {
        color[0] = BG_COLOR_R;
        color[1] = BG_COLOR_G;
        color[2] = BG_COLOR_B;
    } else {
        color[0] = result * objectColor[0];
        color[1] = result * objectColor[1];
        color[2] = result * objectColor[2];
    }
}

/*
 * Split the quad faces of the given object into triangles.
 * The vertices are split using the rule:
 * Quad: v0, v1, v2, v3  -> first Tri : v0, v1, v2
 *                       -> second Tri: v0, v2, v3
 *
 * object: The object containing the faces to split
 */
void splitQuads(Object *object) {

    // check for the number of quads
    int quadNb = 0;
    for (int fId = 0; fId < object->faceNb; fId++) {
        Face current = object->faces[fId];
        if (current.isQuad) {
            quadNb++;
        }
    }
    if (quadNb == 0) return;

    // split the quads
    int newFaceNb = (object->faceNb - quadNb) + 2 * quadNb;
    object->faces = (Face *) realloc(object->faces, sizeof(Face) * newFaceNb);
    int newFaceId = object->faceNb;
    for (int currentFaceId = 0; currentFaceId < object->faceNb; currentFaceId++) {
        Face c = object->faces[currentFaceId];
        if (c.isQuad) {
            Face f;
            for (int i = 0; i < 3; i++) {

                // interchanging the faces
                f.v0[i] = c.v0[i];
                f.v1[i] = c.v2[i];
                f.v2[i] = c.v3[i];
                f.n[i] = c.n[i];
                f.isQuad = false;
            }
            object->faces[newFaceId] = f;
            newFaceId++;
        }
    }
    object->faceNb = newFaceNb;
}

/*
 * For each pixel in the image, trace a ray following the direction of the camera.
 * If the ray intersect a face in the scene, the color is computer.
 *
 * renderArguments: Since this function is meant to be used by multiple threads,
 *                  only one argument can be passed as argument.
 *                  renderArguments is a struct containing the scene, the image channels, etc...
 */
void *renderLoop(void *renderArguments) {

    struct renderArgs *args = (struct renderArgs *) renderArguments;

    // todo the direction of the camera should be computed with the camera wolrd matrix instead
    Ray ray = {.origin={args->scene->camera.origin[0], args->scene->camera.origin[1],
                        args->scene->camera.origin[2]},
            .direction={0, CAM_FOCAL_LENGTH, 0}};

    for (int y = args->start; y < args->end; y++) {

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
                args->red[y][x] = BG_COLOR_R;
                args->green[y][x] = BG_COLOR_G;
                args->blue[y][x] = BG_COLOR_B;
            } else {
                float color[3];
                computeColor(color, nearestFace->n, &args->scene->light, args->scene->object.color);

                args->red[y][x] = color[0];
                args->green[y][x] = color[1];
                args->blue[y][x] = color[2];

            }
        }
    }

    return NULL;
}

/*
 * Helper function to get the number of threads of the current system.
 *
 * return: number of threads available
*/
unsigned int getNumThreads() {

    unsigned int eax = 11, ebx = 0, ecx = 1, edx = 0;

    asm volatile("cpuid"
    : "=a" (eax),
    "=b" (ebx),
    "=c" (ecx),
    "=d" (edx)
    : "0" (eax), "2" (ecx)
    : );

    return ebx;
}


/*
 * Given a scene and an image path, It renders the object in the scene and outputs an image.
 *
 * scene: struct containing information about the objects, cameras, lights, etc...
 * imagePath: the output file path of the rendered image.
 */
void render(Scene *scene, char *imagePath) {

    transformObject(&scene->object);

    // Generate arrays of pointers for each color channel.
    // This represents the final image
    float **red = (float **) malloc(RESOLUTION_H * sizeof(float *));
    float **green = (float **) malloc(RESOLUTION_H * sizeof(float *));
    float **blue = (float **) malloc(RESOLUTION_H * sizeof(float *));
    for (int i = 0; i < RESOLUTION_H; i++) {
        red[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
        green[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
        blue[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
    }

    struct timespec startTime, finishTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);

    unsigned int threadCount = getNumThreads();
    printf("Using %d threads\n", threadCount);
    pthread_t threads[threadCount];

    // submit multi-threaded render loop.
    int start = 0;
    int lineIncrement = RESOLUTION_H / threadCount;
    struct renderArgs arguments[threadCount];

    for (unsigned int i = 0; i < threadCount; ++i) {
        pthread_t t;

        struct renderArgs args1 = {.scene=scene, .red=red, .green=green,
                .blue=blue, .start=start, .end=start + lineIncrement, .threadId=i};
        arguments[i] = args1;

        pthread_create(&t, NULL, &renderLoop, (void *) &arguments[i]);
        threads[i] = t;
        start += lineIncrement;
    }

    for (unsigned int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print render time taking multithreading into consideration
    clock_gettime(CLOCK_MONOTONIC, &finishTime);
    double elapsed = (double) (finishTime.tv_sec - startTime.tv_sec);
    elapsed += (double) ((finishTime.tv_nsec - startTime.tv_nsec) / 1000000000.0);
    printf("\nrender time: %f s\n", (float) elapsed);

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
