
#include <stddef.h>
#include <stdio.h>
#include "geometries.h"

void printFaces(Face* head){
    Face* displayHead = head;
    int faceID = 1;
    while(displayHead != NULL){
        for (int vertexId = 0; vertexId < 3; vertexId++){
            printf("face %d: vertex %d: %f %f %f\n", faceID, vertexId, *(displayHead->v0 + 0), *(displayHead->v0 + 1), *(displayHead->v0 + 2));
        }

        displayHead = (Face *) displayHead->next;
        faceID++;
    }
}