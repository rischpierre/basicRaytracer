//
// Created by pierre on 2021-09-07.
//

#include "test_vector.h"
#include "vector.h"
#include "stdio.h"

void test_cross_product_is_valid(){
    struct Vector v1;
    v1.x = 1;
    v1.y = 0;
    v1.z = 0;

    struct Vector v2;
    v2.x = 0;
    v2.y = 1;
    v2.z = 0;
    struct Vector test = crossProduct(v1, v2);

    if (test.x == 1 && test.y == 0 && test.z == 1) {
        printf("success cross product");
    }
}
