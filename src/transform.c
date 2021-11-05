
#include "transform.h"
#include "mathLib.h"
#include "renderSettings.h"
#include <math.h>
#include <float.h>
#include <stdio.h>


void transform(float *v, float *tm){
    float matrix44fTranslate[16]= {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            tm[0], tm[1], tm[2], 1
    };

    float rxMatrix[16] = {
            1, 0, 0, 0,
            0, cosf(tm[3]),  -sinf(tm[3]) , 0,
            0, sinf(tm[3]), cosf(tm[3]), 0,
            0 , 0 , 0 ,1
    };

    float ryMatrix[16] = {
            cosf(tm[4]), 0, sinf(tm[4]), 0,
            0, 1,  0, 0,
            -sinf(tm[4]), 0, cosf(tm[4]), 0,
            0 , 0 , 0 , 1
    };

    float rzMatrix[16] = {
            cosf(tm[5]), -sinf(tm[5]), 0, 0,
            sinf(tm[5]), cosf(tm[5]), 0, 0,
            0, 0, 1, 0,
            0 , 0 , 0 , 1
    };

    float scaleMatrix[16] = {
            tm[6], 0, 0, 0,
            0, tm[7],  0, 0,
            0, 0, tm[8], 0,
            0 , 0 , 0 ,1
    };

    multVectMatrix44(v, scaleMatrix);
    multVectMatrix44(v, rxMatrix);
    multVectMatrix44(v, ryMatrix);
    multVectMatrix44(v, rzMatrix);
    multVectMatrix44(v, matrix44fTranslate);
}


void printBBox(const float* bbox){

    printf("bbox: x-: %f x+ %f  |  ", bbox[0], bbox[1]);
    printf("y-: %f y+: %f  |   ", bbox[2], bbox[3]);
    printf("z-: %f z+: %f", bbox[4], bbox[5]);
    printf("\n");
}


void transformObject(Object *object, float* tm){

    for (int i = 0; i < object->faceNb; ++i) {

        transform(object->faces[i].v0, tm);
        transform(object->faces[i].v1, tm);
        transform(object->faces[i].v2, tm);
    }

}

void computeBBox(const Object *o, float* bbox){

    float maxCoordX = -WORLD_MAX_DISTANCE;
    float maxCoordY = -WORLD_MAX_DISTANCE;
    float maxCoordZ = -WORLD_MAX_DISTANCE;

    float minCoordX = WORLD_MAX_DISTANCE;
    float minCoordY = WORLD_MAX_DISTANCE;
    float minCoordZ = WORLD_MAX_DISTANCE;

    Face *current;
    for (int i = 0; i < o->faceNb; i++) {
        current = &o->faces[i];

        // loop over every vertex in the face
        for(int v=0; v < 3; v++){
            // loop over attributes of struct
            float x = *(current->v0 + 3 * v + 0);
            float y = *(current->v0 + 3 * v + 1);
            float z = *(current->v0 + 3 * v + 2);

            if (x < minCoordX)
                minCoordX = x;
            if (x > maxCoordX)
                maxCoordX = x;

            if (y < minCoordY)
                minCoordY = y;
            if (y > maxCoordY)
                maxCoordY = y;

            if (z < minCoordZ)
                minCoordZ = z;
            if (z > maxCoordZ)
                maxCoordZ = z;        }
    }

    bbox[0] = minCoordX;
    bbox[1] = maxCoordX;

    bbox[2] = minCoordY;
    bbox[3] = maxCoordY;

    bbox[4] = minCoordZ;
    bbox[5] = maxCoordZ;

}