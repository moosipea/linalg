#include "math.h"
#include "linalg.h"

/*
* Vec4 functions
*/

struct LINALG(Vec4) LINALG(Vec4_create)(float x, float y, float z, float w) {
    struct LINALG(Vec4) res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

struct LINALG(Vec4) LINALG(Vec4_add)(struct LINALG(Vec4) v0, struct LINALG(Vec4) v1) {
    struct LINALG(Vec4) res;
    res.x = v0.x + v1.x;
    res.y = v0.y + v1.y;
    res.z = v0.z + v1.z;
    res.w = v0.w + v1.w;
    return res;
}

struct LINALG(Vec4) LINALG(Vec4_sub)(struct LINALG(Vec4) v0, struct LINALG(Vec4) v1) {
    struct LINALG(Vec4) res;
    res.x = v0.x - v1.x;
    res.y = v0.y - v1.y;
    res.z = v0.z - v1.z;
    res.w = v0.w - v1.w;
    return res;
}

struct LINALG(Vec4) LINALG(Vec4_mul)(struct LINALG(Vec4) v, float k) {
    struct LINALG(Vec4) res;
    res.x = v.x*k;
    res.y = v.y*k;
    res.z = v.z*k;
    res.w = v.w*k;
    return res;
}

struct LINALG(Vec4) LINALG(Vec4_div)(struct LINALG(Vec4) v, float k) {
    struct LINALG(Vec4) res;
    res.x = v.x / k;
    res.y = v.y / k;
    res.z = v.z / k;
    res.w = v.w / k;
    return res;
}

float LINALG(Vec4_mag)(struct LINALG(Vec4) v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

struct LINALG(Vec4) LINALG(Vec4_norm)(struct LINALG(Vec4) v) {
    struct LINALG(Vec4) res;
    float mag;
    res = v;
    mag = LINALG(Vec4_mag)(v);
    return LINALG(Vec4_div)(res, mag);
}

float LINALG(Vec4_dot)(struct LINALG(Vec4) v0, struct LINALG(Vec4) v1) {
    return v0.x*v1.x + v0.y*v1.y + v0.z*v1.z + v0.w*v1.w;
}

/*
* Mat4x4 functions
*/

struct LINALG(Mat4x4) LINALG(Mat4x4_ident)(void) {
    struct LINALG(Mat4x4) mat = {0};
    mat.m[0][0] = 1.0f;
    mat.m[1][1] = 1.0f;
    mat.m[2][2] = 1.0f;
    mat.m[3][3] = 1.0f;
    return mat;
}

void LINALG(Mat4x4_matmul)(struct LINALG(Mat4x4) *with, struct LINALG(Mat4x4) *mat) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            mat->m[y][x] = mat->m[y][0]*with->m[0][x] +
                           mat->m[y][1]*with->m[1][x] +
                           mat->m[y][2]*with->m[2][x] +
                           mat->m[y][3]*with->m[3][x];
        }
    }
}

struct LINALG(Mat4x4) LINALG(Mat4x4_translation)(float dx, float dy, float dz) {
    struct LINALG(Mat4x4) mat = LINALG(Mat4x4_ident)();
    mat.m[0][3] = dx;
    mat.m[1][3] = dx;
    mat.m[2][3] = dx;
    return mat;
}

struct LINALG(Mat4x4) LINALG(Mat4x4_scaling)(float sx, float sy, float sz) {
    struct LINALG(Mat4x4) mat = LINALG(Mat4x4_ident)();
    mat.m[0][0] = sx;
    mat.m[1][1] = sx;
    mat.m[2][2] = sx;
    return mat;
}

struct LINALG(Mat4x4) LINALG(Mat4x4_rotation_x)(float r);
struct LINALG(Mat4x4) LINALG(Mat4x4_rotation_y)(float r);
struct LINALG(Mat4x4) LINALG(Mat4x4_rotation_z)(float r);

struct LINALG(Mat4x4) LINALG(Mat4x4_rotation)(float rx, float ry, float rz) {
    struct LINALG(Mat4x4) mat_z = LINALG(Mat4x4_rotation_z)(rz);
    struct LINALG(Mat4x4) mat_x = LINALG(Mat4x4_rotation_x)(rx);
    struct LINALG(Mat4x4) mat_y = LINALG(Mat4x4_rotation_y)(ry);
    LINALG(Mat4x4_matmul)(&mat_x, &mat_z);
    LINALG(Mat4x4_matmul)(&mat_y, &mat_z);
    return mat_z;
}

struct LINALG(Mat4x4) LINALG(Mat4x4_perspective)(float fovy, float aspect, float near, float far);