
#include "../src/raytracer.h"

#include "gtest/gtest.h"
#include "../src/ioLib.h"

TEST(raytracer, test_ray_inside_triangle){
    Ray ray = {.origin={0, 0, 0},
               .direction={0, 1, 0}};

    Scene s;
    parseObjFile(&s, "../../examples/triangle.obj");
    ASSERT_TRUE(isRayIntersectsTriangle(&ray, s.object.faces, true));
}

TEST(raytracer, test_ray_outside_triangle){
    Ray ray = {.origin={0, 0, 0},
            .direction={0, 1, 0}};

    Scene s;
    parseObjFile(&s, "../../examples/notIntersectingYTriangle.obj");
    ASSERT_FALSE(isRayIntersectsTriangle(&ray, s.object.faces, true));
}

TEST(raytracer, test_back_face){
    Ray ray = {.origin={0, 0, 0},
            .direction={0, 1, 0}};

    Scene s;
    parseObjFile(&s, "../../examples/reversedTriangle.obj");
    ASSERT_FALSE(isRayIntersectsTriangle(&ray, s.object.faces, true));
}

TEST(raytracer, test_ray_inside_tilted_triangle){
    Ray ray = {.origin={0, 0, 0},
            .direction={0, 1, 0}};

    Scene s;
    parseObjFile(&s, "../../examples/tiltedTriangle.obj");
    ASSERT_TRUE(isRayIntersectsTriangle(&ray, s.object.faces, true));
}

TEST(computeColor, test_computeColor){
    DirLight light = {.direction={1, 0, 0}};
    float faceN[3] = {-1, 0, 0};

    ASSERT_EQ(computeColor(faceN, &light), 1.f);

    faceN[0] = -0.5f;
    faceN[1] = -0.5f;
    faceN[2] = 0;
    ASSERT_FLOAT_EQ(computeColor(faceN, &light), 0.5f);

    faceN[0] = 1.f;
    faceN[1] = 0;
    faceN[2] = 0;
    ASSERT_FLOAT_EQ(computeColor(faceN, &light), 0);
}

