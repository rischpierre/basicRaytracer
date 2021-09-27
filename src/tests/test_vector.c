
#include <assert.h>
#include <math.h>
#include "../vector.h"
#include "stdbool.h"
#include "../utils.h"



void test_cross_product_is_valid(){
    Vector v1;
    v1.x = 1;
    v1.y = 0;
    v1.z = 0;

    Vector v2;
    v2.x = 0;
    v2.y = 1;
    v2.z = 0;
    Vector test = crossProduct(&v1, &v2);

    if (test.x == 0 && test.y == 0 && test.z == 1) {
        print_result(true, __func__ );
    } else{
        print_result(false, __func__ );
    }
}

void test_dot_product_is_valid(){
    Vector v1;
    v1.x = 1;
    v1.y = 2;
    v1.z = 2;

    Vector v2;
    v2.x = 0;
    v2.y = 1;
    v2.z = 4;

    if (dotProduct(&v1, &v2) == 10) {
        print_result(true, __func__ );
    } else{
        print_result(false, __func__ );
    }
}


void test_multVectMatrix44(){
    float matrix44fTranslate[16]= {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 2, 2, 1 };
    float vector[4] = {1, 1, 1, 1};
    float vectorExpected[4] = {3, 3, 3, 1};

    multVectMatrix44(vector, matrix44fTranslate);

    for(int i =0; i < 4; i++) {
        assert(vector[i] == vectorExpected[i]);
    }

}


void test_angleBetweenVectors(){
    Vector v1;
    Vector v2;
    v1.x = 1;
    v1.y = 0;
    v1.z = 0;

    v2.x = 0;
    v2.y = 1;
    v2.z = 0;

    assert(angleBetweenVectors(&v1, &v2) == (float)M_PI/2);

    v2.x = 1;
    v2.y = 0;
    v2.z = 0;
    assert(angleBetweenVectors(&v1, &v2) == 0);

    v2.x = -1;
    v2.y = 0;
    v2.z = 0;
    assert(angleBetweenVectors(&v1, &v2) == (float)M_PI);
}