#include <math.h>
#include "stdbool.h"
#include "../vector.h"
#include "../utils.h"

#include <criterion/criterion.h>


Test(vector_tests, cross_product) {
    Vector v1;
    v1.x = 1;
    v1.y = 0;
    v1.z = 0;

    Vector v2;
    v2.x = 0;
    v2.y = 1;
    v2.z = 0;
    Vector test = crossProduct(&v1, &v2);

    cr_assert(test.x == 0);
    cr_assert(test.y == 0);
    cr_assert(test.z == 1);
}


Test(vector_tests, dot_product){

    Vector v1;
    v1.x = 1;
    v1.y = 2;
    v1.z = 2;

    Vector v2;
    v2.x = 0;
    v2.y = 1;
    v2.z = 4;

    cr_assert_eq(dotProduct(&v1, &v2), 10);
}


Test(vector_tests, test){

    float matrix44fTranslate[16]= {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 2, 2, 1 };
    float vector[4] = {1, 1, 1, 1};
    float vectorExpected[4] = {3, 3, 3, 1};

    multVectMatrix44(vector, matrix44fTranslate);

    for(int i =0; i < 4; i++) {
        cr_assert_eq(vector[i], vectorExpected[i]);
    }

}


Test(vector_tests, angle_between_vectors){
    Vector v1;
    Vector v2;
    v1.x = 1;
    v1.y = 0;
    v1.z = 0;

    v2.x = 0;
    v2.y = 1;
    v2.z = 0;

    cr_assert_eq(angleBetweenVectors(&v1, &v2), (float)M_PI/2);

    v2.x = 1;
    v2.y = 0;
    v2.z = 0;
    cr_assert_eq(angleBetweenVectors(&v1, &v2), 0);

    v2.x = -1;
    v2.y = 0;
    v2.z = 0;
    cr_assert_eq(angleBetweenVectors(&v1, &v2), (float)M_PI);
}