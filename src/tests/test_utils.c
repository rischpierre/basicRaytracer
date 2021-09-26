

#include <assert.h>
#include "test_utils.h"

void test_interpolation1d(){

    assert(interpolation1d(50, 0, 100, -3, 3) == 0.0);
    assert(interpolation1d(10, 0, 100, -10, 10) == -8);

}