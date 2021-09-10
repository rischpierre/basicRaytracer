
#include "test_raytracer.h"
#include "utils.h"
#include "raytracer.h"

void test_ray_inside_triangle(){
    Ray ray;

    ray.v.x = 1;
    ray.v.y = 0;
    ray.v.z = 0;

    Face f1;

    f1.v0.x = 10;
    f1.v0.y = 0;
    f1.v0.z = 0;

    f1.v1.x = 10;
    f1.v1.y = 1;
    f1.v1.z = 0;

    f1.v2.x = 10;
    f1.v2.y = 0;
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
