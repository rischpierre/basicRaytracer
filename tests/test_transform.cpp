#include "../src/transform.h"

#include <math.h>

#include "gtest/gtest.h"


TEST(transformTests, translate_works) {
    float v[4] = {0, 0, 0, 1};

    float transformMatrix[9] = {
            2, 4, -2,            // translate
            0, 0, 0,            // rotate in rads: M_PI/4
            1.f, 1.f, 1.f       // scale
    };

    transform(v, transformMatrix);

    float expected[4] = {2, 4, -2, 1};

    for(uint8_t i = 0; i < 4; i++){

        ASSERT_FLOAT_EQ(expected[i], v[i]);
    }
    ASSERT_EQ(1, 3);
}


TEST(transformTests, rotate_works) {
    float v[4] = {1, 0, 0, 1};

    float transformMatrix[9] = {
            0, 0, 0,
            0, M_PI/4, 0,
            1.f, 1.f, 1.f
    };

    transform(v, transformMatrix);

    float expected[4] = {cosf(M_PI/4), 0, 0.5f, 1.f};

    for(uint8_t i = 0; i < 4; i++){

        ASSERT_FLOAT_EQ(expected[i], v[i]);
    }

}

TEST(transformTests, scale_works) {
    float v[4] = {1, 1, 1, 1};

    float transformMatrix[9] = {
            0, 0, 0,
            0, 0, 0,
            .5f, .5f, .5f
    };

    transform(v, transformMatrix);

    float expected[4] = {0.5f, 0.5f, 0.5f, 1.f};
    for(uint8_t i = 0; i < 4; i++){

        ASSERT_FLOAT_EQ(expected[i], v[i]);
    }

}