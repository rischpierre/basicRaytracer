#include "../transform.h"

#include <criterion/criterion.h>
#include <math.h>
#include <stdio.h>


Test(transformTests, translate_works) {
    float v[4] = {0, 0, 0, 1};

    float transformMatrix[9] = {
            2, 4, -2,            // translate
            0, 0, 0,            // rotate in rads: M_PI/4
            1.f, 1.f, 1.f       // scale
    };

    transform(v, transformMatrix);

    float expected[4] = {2, 4, -2, 1};
    cr_assert_arr_eq(v, expected, 4);
}


Test(transformTests, rotate_works) {
    float v[4] = {1, 0, 0, 1};

    float transformMatrix[9] = {
            0, 0, 0,
            0, M_PI/4, 0,
            1.f, 1.f, 1.f
    };

    transform(v, transformMatrix);

    float expected[4] = {cosf(M_PI/4), 0, 0.5f, 1.f};
    cr_assert_arr_eq(v, expected, 4);

}

Test(transformTests, scale_works) {
    float v[4] = {1, 1, 1, 1};

    float transformMatrix[9] = {
            0, 0, 0,
            0, 0, 0,
            .5f, .5f, .5f
    };

    transform(v, transformMatrix);

    float expected[4] = {0.5f, 0.5f, 0.5f, 1.f};
    cr_assert_arr_eq(v, expected, 4);

}