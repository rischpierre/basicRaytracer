

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
    if (dotProduct(ray->direction, face->normal) > 0 && isBackFaceCulled){
        return false;
    }

    // parametric equation of a plane: Ax + By + Cz + D = 0
    // where D is the distance from origin and parallel to the plane's triangle.normal
    float D = dotProduct(face->normal, face->v0);

    float NDotRayDirection = dotProduct(face->normal, ray->direction);
    // check if triangle is parallel to ray. This can cause div by 0 instead
    if (NDotRayDirection == 0) return false;

    // compute the distance between the triangle and the origin of the ray
    float t = -(dotProduct(face->normal,  ray->origin) + (float)fabs((double)D)) / NDotRayDirection;

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
    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    float edge1[3];
    subVectors(edge1, face->v2, face->v1, 3);

    float C1[3];
    subVectors(C1, Phit, face->v1, 3);

    crossProduct(tmpCrossProduct, edge1, C1);

    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

    float edge2[3];
    subVectors(edge2, face->v0, face->v2, 3);

    float C2[3];
    subVectors(C2, Phit, face->v2, 3);

    crossProduct(tmpCrossProduct, edge2, C2);
    if (dotProduct(face->normal, tmpCrossProduct) < 0) return false;

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

void splitQuads(Object * o){
    int quads = 0;
    for(int fId = 0; fId < o->faceNb; fId++){
        Face current = o->faces[fId];
        if (current.isQuad){
           quads++;
        }
    }
    if (quads == 0) return;

    int faceNb = (o->faceNb - quads) + 2 * quads;
    Face *newFaces = (Face*)malloc(sizeof(Face) * faceNb);
    Face f;
    int newFaceIncr = 0;
    for(int fId = 0; fId < o->faceNb; fId++) {
        Face c = o->faces[fId];
        if (c.isQuad) {
            for(int i = 0; i < 3; i++){

                f.v0[i] = c.v0[i];
                f.v1[i] = c.v2[i];
                f.v2[i] = c.v3[i];
                f.normal[i] = c.normal[i];
            }

            newFaces[newFaceIncr] = c;
            newFaceIncr++;
            newFaces[newFaceIncr] = f;
            newFaceIncr++;
        } else {
            newFaces[newFaceIncr];
            newFaceIncr++;
        }
    }
    o->faces = newFaces;
    o->faceNb = faceNb;
}


void render(Scene *scene){
    // this is first a test with planar projection

    Ray ray = {.origin={0, 0, 0},
            .direction={0, CAM_FOCAL_LENGTH, 0}};

    float **red = (float **) malloc(RESOLUTION_X * sizeof(float *));
    float **green = (float **) malloc(RESOLUTION_X * sizeof(float *));
    float **blue = (float **) malloc(RESOLUTION_X * sizeof(float *));
    for (uint16_t i = 0; i < RESOLUTION_X; i++) {
        red[i] = (float *) malloc(RESOLUTION_Y * sizeof(float));
        blue[i] = (float *) malloc(RESOLUTION_Y * sizeof(float));
        green[i] = (float *) malloc(RESOLUTION_Y * sizeof(float));
    }

    clock_t start = clock();
    printObject(&scene->object);
//    splitQuads(&scene->object);
//    printf("after\n");
//    printObject(&scene->object);

    // scanline process from top left to bottom right
    for (int y = RESOLUTION_Y; y >= 0; y--) {
        for (int x = 0; x < RESOLUTION_X; x++) {

            // world: x -> screen: x
            // world: z -> screen: y
            ray.direction[0] = interpolation1d((float) x, 0, (float) RESOLUTION_X, -CAM_FILM_SIZE_X / 2,
                                            CAM_FILM_SIZE_X / 2);

            ray.direction[2] = interpolation1d((float) y, 0, (float) RESOLUTION_Y, -CAM_FILM_SIZE_Y / 2,
                                            CAM_FILM_SIZE_Y / 2);


            for (int i = 0; i < scene->object.faceNb; i++){
                Face* currentFace = &scene->object.faces[i];

                bool intersected = isRayIntersectsTriangle(&ray, currentFace, true);
                if (intersected) {
                    float color = computeColor(currentFace->normal, &scene->light);
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
    writeBmpFile(RESOLUTION_X, RESOLUTION_Y, red, green, blue, imagePath);

    printf("Wrote image : %s", imagePath);

    for (uint16_t i = 0; i < RESOLUTION_X; i++) {
        free(red[i]);
        free(green[i]);
        free(blue[i]);
    }

    free(red);
    free(green);
    free(blue);

}