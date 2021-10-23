
#include "../src/raytracer.h"

#include "gtest/gtest.h"
#include "../src/ioLib.h"

TEST(raytracer, test_ray_inside_triangle){
    Ray ray = {.origin={0, 0, 0},
               .direction={0, 1, 0}};

    Scene s;
    parseObjFile(&s, "../examples/triangle.obj");
    ASSERT_TRUE(isRayIntersectsTriangle(&ray, s.object.faces));
}
//
//TEST(raytracer, test_ray_outside_triangle){
//    Ray ray = {.origin={0, 0, 0},
//               .direction={1, 0, 0}};
//
//    // defining a triangle that is not in the sight of the ray
//    Face f1 = {.v0={2, 2, 2},
//               .v1={2, -1, 1},
//               .v2={2, -1, 3},
//               .normal={-1, 0, 0}};
//
//    ASSERT_FALSE(isRayIntersectsTriangle(&ray, &f1));
//}
//
//TEST(raytracer, test_ray_inside_tilted_triangle){
//    Ray ray = {.origin={0, 0, 0},
//            .direction={1, 0, 0}};
//
//    // defining a triangle that is not in the sight of the ray
//    Face f1 = {.v0={1, 2, 2},
//            .v1={2, -1, 1},
//            .v2={1, -1, 3},
//            .normal={-1, 0, 0}};
//
//    ASSERT_FALSE(isRayIntersectsTriangle(&ray, &f1));
//}
//
//TEST(computeColor, test_computeColor){
//    DirLight light = {.direction={1, 0, 0}};
//    float faceN[3] = {-1, 0, 0};
//
//    ASSERT_EQ(computeColor(faceN, &light), 1.f);
//
//    faceN[0] = -0.5f;
//    faceN[1] = -0.5f;
//    faceN[2] = 0;
//    ASSERT_FLOAT_EQ(computeColor(faceN, &light), 0.5f);
//
//    faceN[0] = 1.f;
//    faceN[1] = 0;
//    faceN[2] = 0;
//    ASSERT_FLOAT_EQ(computeColor(faceN, &light), 0);
//}
//
