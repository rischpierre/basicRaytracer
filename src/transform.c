
#include "transform.h"
#include "mathLib.h"
#include <math.h>


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