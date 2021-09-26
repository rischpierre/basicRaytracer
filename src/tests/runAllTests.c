
#include "test_raytracer.h"
#include "test_vector.h"
#include "test_utils.h"
#include "test_bmpWriter.h"

int main(){

    test_ray_outside_triangle();
    test_ray_inside_triangle();
    test_interpolation1d();
    test_cross_product_is_valid();
    test_dot_product_is_valid();
    test_bmpWriter();

    return 0;
}
