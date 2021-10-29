
#include "../src/raytracer.h"

#include "gtest/gtest.h"
#include "../src/ioLib.h"
#include "../src/renderSettings.h"

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

TEST(raytracer, test_ray_outside_tilted_triangle){
    Ray ray = {.origin={0, 0, -1.2f},
            .direction={0, 1, 0}};

    Scene s;
    parseObjFile(&s, "../../examples/tiltedTriangle.obj");
    ASSERT_FALSE(isRayIntersectsTriangle(&ray, s.object.faces, true));
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
    ASSERT_FLOAT_EQ(computeColor(faceN, &light), AMBIENT_CONTRIBUTION);
}

TEST(split_quads, test_only_tri_faces){

    Object o;
    Face f= {.isQuad=false};
    Face f2= {.isQuad=false};
    Face faces[2] = {f2, f};
    o.faces = faces;
    o.faceNb = 2;

    splitQuads(&o);
    ASSERT_EQ(o.faceNb, 2);
}

TEST(split_quads_2, test_with_quad_faces){

    Object o;
    Face f= {.v0={1, 2, 3}, .v1 ={4, 5, 6}, .v2={7, 8, 9}, .v3={10, 11, 12}, .isQuad=true, .n={13, 14, 15}};
    Face faces[1] = {f};
    o.faces = faces;
    o.faceNb = 1;

    splitQuads(&o);

    ASSERT_EQ(o.faceNb, 2);
    ASSERT_EQ(o.faces[0].v0[0], 1);
    ASSERT_EQ(o.faces[0].v1[2], 6);

    ASSERT_EQ(o.faces[1].v0[0], 1);
    ASSERT_EQ(o.faces[1].v1[2], 9);

    ASSERT_EQ(o.faces[1].n[0], 13);
    ASSERT_EQ(o.faces[1].n[2], 15);
}

