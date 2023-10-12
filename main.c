#include <stdio.h>

#define LINALG_INLINE_FUNCTIONS
#include "linalg.h"

int main(void) {
#if 0
    struct linalg_Vec4 a = linalg_Vec4_create(0, 0, 0, 0);
    linalg_Vec4_add(&a, linalg_Vec4_create(1, 2, 3, 4));
    linalg_Vec4_sub(&a, linalg_Vec4_create(0, 3, 0, -1));

    printf("Result: { x: %f, y: %f, z: %f, w: %f}\n", a.x, a.y, a.z, a.w);

#endif
    return 0;
}