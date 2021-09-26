


#include "utils.h"

void print_result(const bool success, const char *function) {
    if (success) {
        printf("PASS: %s\n", function);
    }else {
        printf("FAIL: %s\n", function);
    }
}



float interpolation1d(float x, float x1, float x2, float y1, float y2){

    return ((y2 - y1) * x + x2 * y1 - x1 * y2) / (x2 - x1);

}