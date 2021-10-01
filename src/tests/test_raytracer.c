
#include "../raytracer.h"

#include "criterion/criterion.h"


Test(raytracer, test_ray_inside_triangle){
    Ray ray = {{0, 0, 0},
               {1, 0, 0}};

    // defining a triangle that is in the sight of the ray
    Face f1 = {{2, 2, 0},
               {2, -1, -1},
               {2, -1, 1},
               {-1, 0, 0}};

    cr_assert(isRayIntersectsTriangle(&ray, &f1));

}

Test(raytracer, test_ray_outside_triangle){
    Ray ray = {{0, 0, 0},
               {1, 0, 0}};

    // defining a triangle that is not in the sight of the ray
    Face f1 = {{2, 2, 2},
               {2, -1, 1},
               {2, -1, 2},
               {-1, 0, 0}};

    cr_assert(! isRayIntersectsTriangle(&ray, &f1));

}
