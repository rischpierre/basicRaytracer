#include <math.h>
#include <bits/types/clock_t.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include "raytracer.h"
#include "mathLib.h"
#include "renderSettings.h"
#include "ioLib.h"
#include "transform.h"


bool isRayIntersectsTriangle(const Ray *ray, const Face *face, bool isBackFaceCulled){

    // skip if the face is back
    if (dotProduct(ray->direction, face->n) > 0 && isBackFaceCulled){
        return false;
    }

    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's triangle.normal
    float D = dotProduct(face->n, face->v0);

    float NDotRayDirection = dotProduct(face->n, ray->direction);
    // check if triangle is parallel to ray. This can cause div by 0 instead
    if (NDotRayDirection == 0) return false;

    // compute the distance between the triangle and the origin of the ray
    float t = -(dotProduct(face->n, ray->origin) + (float)fabs((double)D)) / NDotRayDirection;

    // triangle is behind the ray
    if (t < 0 ) return false;

    float tmpCross[3];

    crossProductFloat(tmpCross, ray->direction, &t, 3);
    float Phit[3];

    addVectors(Phit, ray->origin, tmpCross, 3);

    // check if Phit is inside triangle
    float edge0[3];
    subVectors(edge0, face->v1, face->v0, 3);

    float C0[3];
    subVectors(C0, Phit, face->v0, 3);

    float tmpCrossProduct[3];
    crossProduct(tmpCrossProduct, edge0, C0);

    // P is on the right side
    if (dotProduct(face->n, tmpCrossProduct) < 0) return false;

    float edge1[3];
    subVectors(edge1, face->v2, face->v1, 3);

    float C1[3];
    subVectors(C1, Phit, face->v1, 3);

    crossProduct(tmpCrossProduct, edge1, C1);

    if (dotProduct(face->n, tmpCrossProduct) < 0) return false;

    float edge2[3];
    subVectors(edge2, face->v0, face->v2, 3);

    float C2[3];
    subVectors(C2, Phit, face->v2, 3);

    crossProduct(tmpCrossProduct, edge2, C2);
    if (dotProduct(face->n, tmpCrossProduct) < 0) return false;

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

    int newFaceId = o->faceNb;
    for(int currentFaceId = 0; currentFaceId < o->faceNb; currentFaceId++) {
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


void render(Scene *scene){
    // this is first a test with planar projection

    Ray ray = {.origin={0, 0, 0},
            .direction={0, CAM_FOCAL_LENGTH, 0}};

    float **red = (float **) malloc(RESOLUTION_H * sizeof(float *));
    float **green = (float **) malloc(RESOLUTION_H * sizeof(float *));
    float **blue = (float **) malloc(RESOLUTION_H * sizeof(float *));
    for (int i = 0; i < RESOLUTION_H; i++) {
        red[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
        green[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
        blue[i] = (float *) malloc(RESOLUTION_W * sizeof(float));
    }

    clock_t start = clock();

    splitQuads(&scene->object);

    // scanline process from top left to bottom right
    for (int y = RESOLUTION_H - 1; y >= 0; y--) {

        // log progress
        int percent = (int)(((float)RESOLUTION_H - (float)y)/(float)RESOLUTION_H * 100);
        printf("%d %% \r", percent);

        for (int x = 0; x < RESOLUTION_W; x++) {

            // world: x -> screen: x
            // world: z -> screen: y
            ray.direction[0] = interpolation1d((float) x, 0, (float) RESOLUTION_W, -CAM_FILM_SIZE_W / 2,
                                               CAM_FILM_SIZE_W / 2);

            ray.direction[2] = interpolation1d((float) y, 0, (float) RESOLUTION_H, -CAM_FILM_SIZE_H / 2,
                                               CAM_FILM_SIZE_H / 2);


            for (int i = 0; i < scene->object.faceNb; i++){
                Face* currentFace = &scene->object.faces[i];

                // intersected or not
                bool intersected = isRayIntersectsTriangle(&ray, currentFace, true);
                if (intersected) {
                    float color = computeColor(currentFace->n, &scene->light);
                    red[y][x] = color;
                    green[y][x] = color;
                    blue[y][x] = color;
                    break;

                } else {
                    red[y][x] = 0;
                    green[y][x] = 0;
                    blue[y][x] = 0;
                }
            }
        }
    }

    clock_t end = clock();
    printf("\nrender time: %f s\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
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
