
#include "../src/raytracer.h"

#include "gtest/gtest.h"

TEST(raytracer, test_ray_inside_triangle){
    Ray ray = {.origin={0, 0, 0},
               .direction={1, 0, 0}};

    // defining a triangle that is in the sight of the ray
    Face f1 = {.v0={2, 2, 0},
               .v1={2, -1, -1},
               .v2={2, -1, 1},
               .normal={-1, 0, 0}};

    ASSERT_TRUE(isRayIntersectsTriangle(&ray, &f1));
}

TEST(raytracer, test_ray_outside_triangle){
    Ray ray = {.origin={0, 0, 0},
               .direction={1, 0, 0}};

    // defining a triangle that is not in the sight of the ray
    Face f1 = {.v0={2, 2, 2},
               .v1={2, -1, 1},
               .v2={2, -1, 2},
               .normal={-1, 0, 0}};

    ASSERT_FALSE(isRayIntersectsTriangle(&ray, &f1));
}
