#include <stdio.h>
#include "geometries.h"


void printObject(const Object *o, bool details){
    printf("Object: %s\n", o->name);
    printf("nb of faces: %d\n", o->faceNb);
    if (details == true){
        for (int faceId = 0; faceId < o->faceNb; faceId++){
            printf("----------------------\n");
            Face curr = o->faces[faceId];
            printf("Face %d\n", faceId);
            printf("  v0: %f %f %f\n", curr.v0[0], curr.v0[1], curr.v0[2]);
            printf("  v1: %f %f %f\n", curr.v1[0], curr.v1[1], curr.v1[2]);
            printf("  v2: %f %f %f\n", curr.v2[0], curr.v2[1], curr.v2[2]);
            printf("  n:  %f %f %f\n", curr.n[0], curr.n[1], curr.n[2]);
        }
    }
    printf("----------------------\n");
}


void computeBBox(const Object *o, float* bbox){

    float maxCoordX = 0;
    float maxCoordY = 0;
    float maxCoordZ = 0;

    float minCoordX = 0;
    float minCoordY = 0;
    float minCoordZ = 0;
    Face *current;
    for (int i = 0; i < o->faceNb; i++) {
        current = &o->faces[i];
        for(int v=0; v < 3; v++){
            // todo how to loop over attributes in a struct using
            int structOffset = v * 3 * sizeof(float)
            float x = *(current->v0 + structOffset));
            float y = *(current->v0 + (v * 3 * sizeof(float)) + 1);
            float z = *(current->v0 + (v * 3 * sizeof(float)) + 2);


        }
    }
}