

#include <criterion/criterion.h>
#include "../utils.h"

Test(dangerous_add, test_passing) {

    cr_assert(interpolation1d(50, 0, 100, -3, 3) == 0.0);
    cr_assert(interpolation1d(10, 0, 100, -10, 10) == -8);
}