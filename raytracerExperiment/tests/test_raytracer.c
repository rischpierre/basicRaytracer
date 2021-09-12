
#include "test_raytracer.h"
#include "utils.h"
#include "raytracer.h"



void test_ray_inside_triangle(){
    Ray ray;

    ray.direction.x = 1;
    ray.direction.y = 0;
    ray.direction.z = 0;

    ray.origin.x = 0;
    ray.origin.y = 0;
    ray.origin.z = 0;

    // defining a triangle that is in the sight of the ray
    Face f1;

    f1.normal.x = -1;
    f1.normal.y = 0;
    f1.normal.z = 0;

    f1.v0.x = 2;
    f1.v0.y = 2;
    f1.v0.z = 0;

    f1.v1.x = 2;
    f1.v1.y = -1;
    f1.v1.z = -1;

    f1.v2.x = 2;
    f1.v2.y = -1;
    f1.v2.z = 1;


    bool intersected = isRayIntersectsTriangle( ray, f1);

    if (intersected) {
        print_result(true, __func__ );
    }else{
        print_result(false,  __func__ );
    }

}
void test_ray_outside_triangle(){

}
