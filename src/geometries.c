#include <stdio.h>
#include "geometries.h"


void printObject(const Object *o){
    printf("Object: %s", o->name);
    printf("nb of faces: %d\n", o->faceNb);
    for (int faceId = 0; faceId < o->faceNb; faceId++){
        printf("----------------------\n");
        Face curr = o->faces[faceId];
        printf("Face %d\n", faceId);
        printf("  v0: %f %f %f\n", curr.v0[0], curr.v0[1], curr.v0[2]);
        printf("  v1: %f %f %f\n", curr.v1[0], curr.v1[1], curr.v1[2]);
        printf("  v2: %f %f %f\n", curr.v2[0], curr.v2[1], curr.v2[2]);
        printf("  n:  %f %f %f\n", curr.normal[0], curr.normal[1], curr.normal[2]);

    }
    printf("----------------------\n");
}