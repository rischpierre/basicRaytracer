


#include "utils.h"

void print_result(const bool success, const char *function) {
    if (success) {
        printf("PASS: %s\n", function);
    }else {
        printf("FAIL: %s\n", function);
    }
}