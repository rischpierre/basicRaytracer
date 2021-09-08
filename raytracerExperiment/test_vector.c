//
// Created by pierre on 2021-09-07.
//

#include "test_vector.h"
#include "vector.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"


void print_result(const bool success, const char *function) {
    if (success) {
        printf("PASS: %s\n", function);
    }else {
        printf("FAIL: %s\n", function);
    }
}

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

    if (test.x == 0 && test.y == 0 && test.z == 1) {
        print_result(true, __func__ );
    } else{
        print_result(false, __func__ );
    }
}

void test_dot_product_is_valid(){
    struct Vector v1;
    v1.x = 1;
    v1.y = 2;
    v1.z = 2;

    struct Vector v2;
    v2.x = 0;
    v2.y = 1;
    v2.z = 4;
    if (dotProduct(v1, v2) == 10) {
        print_result(true, __func__ );
    } else{
        print_result(false, __func__ );
    }
}
