#include "linalg.h"
#include <math.h>

/*
 * Vec4 functions
 */

struct linalg_Vec4 linalg_Vec4_create(float x, float y, float z, float w) {
    struct linalg_Vec4 res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

struct linalg_Vec4 linalg_Vec4_sub(struct linalg_Vec4 v0, struct linalg_Vec4 v1) {
    struct linalg_Vec4 res;
    res.x = v0.x - v1.x;
    res.y = v0.y - v1.y;
    res.z = v0.z - v1.z;
    res.w = v0.w - v1.w;
    return res;
}

struct linalg_Vec4 linalg_Vec4_mul(struct linalg_Vec4 v, float k) {
    struct linalg_Vec4 res;
    res.x = v.x * k;
    res.y = v.y * k;
    res.z = v.z * k;
    res.w = v.w * k;
    return res;
}

struct linalg_Vec4 linalg_Vec4_div(struct linalg_Vec4 v, float k) {
    struct linalg_Vec4 res;
    res.x = v.x / k;
    res.y = v.y / k;
    res.z = v.z / k;
    res.w = v.w / k;
    return res;
}

float linalg_Vec4_mag(struct linalg_Vec4 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

struct linalg_Vec4 linalg_Vec4_norm(struct linalg_Vec4 v) {
    struct linalg_Vec4 res;
    float mag;
    res = v;
    mag = linalg_Vec4_mag(v);
    return linalg_Vec4_div(res, mag);
}

float linalg_Vec4_dot(struct linalg_Vec4 v0, struct linalg_Vec4 v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
}

/*
 * Vec3 functions
 */

struct linalg_Vec3 linalg_Vec3_create(float x, float y, float z) {
    struct linalg_Vec3 res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

struct linalg_Vec3 linalg_Vec3_sub(struct linalg_Vec3 v0, struct linalg_Vec3 v1) {
    struct linalg_Vec3 res;
    res.x = v0.x - v1.x;
    res.y = v0.y - v1.y;
    res.z = v0.z - v1.z;
    return res;
}

struct linalg_Vec3 linalg_Vec3_mul(struct linalg_Vec3 v, float k) {
    struct linalg_Vec3 res;
    res.x = v.x * k;
    res.y = v.y * k;
    res.z = v.z * k;
    return res;
}

struct linalg_Vec3 linalg_Vec3_div(struct linalg_Vec3 v, float k) {
    struct linalg_Vec3 res;
    res.x = v.x / k;
    res.y = v.y / k;
    res.z = v.z / k;
    return res;
}

float linalg_Vec3_mag(struct linalg_Vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

struct linalg_Vec3 linalg_Vec3_norm(struct linalg_Vec3 v) {
    struct linalg_Vec3 res;
    float mag;
    res = v;
    mag = linalg_Vec3_mag(v);
    return linalg_Vec3_div(res, mag);
}

float linalg_Vec3_dot(struct linalg_Vec3 v0, struct linalg_Vec3 v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

/*
 * Mat4x4 functions
 */

struct linalg_Mat4x4 linalg_Mat4x4_ident(void) {
    struct linalg_Mat4x4 mat = {0};
    mat.m[0][0] = 1.0f;
    mat.m[1][1] = 1.0f;
    mat.m[2][2] = 1.0f;
    mat.m[3][3] = 1.0f;
    return mat;
}

void linalg_Mat4x4_matmul(struct linalg_Mat4x4 *with, struct linalg_Mat4x4 *mat) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            mat->m[y][x] = mat->m[y][0] * with->m[0][x] + mat->m[y][1] * with->m[1][x] +
                           mat->m[y][2] * with->m[2][x] + mat->m[y][3] * with->m[3][x];
        }
    }
}

struct linalg_Mat4x4 linalg_Mat4x4_translation(float dx, float dy, float dz) {
    struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
    mat.m[0][3] = dx;
    mat.m[1][3] = dy;
    mat.m[2][3] = dz;
    return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_scaling(float sx, float sy, float sz) {
    struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.m[2][2] = sz;
    return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_rotation_x(float r) {
    struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
    mat.m[1][1] = cosf(r);
    mat.m[1][2] = -sinf(r);
    mat.m[2][1] = sinf(r);
    mat.m[2][2] = cosf(r);
    return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_rotation_y(float r) {
    struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
    mat.m[0][0] = cosf(r);
    mat.m[0][2] = sinf(r);
    mat.m[2][0] = -sinf(r); 
    mat.m[2][2] = cosf(r);
    return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_rotation_z(float r) {
    struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
    mat.m[0][0] = cosf(r);
    mat.m[0][1] = -sinf(r); 
    mat.m[1][0] = sinf(r);
    mat.m[1][1] = cosf(r);
    return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_rotation(float rx, float ry, float rz) {
    struct linalg_Mat4x4 mat_x = linalg_Mat4x4_rotation_x(rx);
    struct linalg_Mat4x4 mat_z = linalg_Mat4x4_rotation_z(rz);
    struct linalg_Mat4x4 mat_y = linalg_Mat4x4_rotation_y(ry);
    /* N.B! Order of multiplication is important here */
    linalg_Mat4x4_matmul(&mat_x, &mat_z);
    linalg_Mat4x4_matmul(&mat_y, &mat_z);
    return mat_z;
}

struct linalg_Mat4x4 linalg_Mat4x4_perspective(float fov_y, float aspect, float near, float far) {
    struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
    float tan_half_fovy = tanf(fov_y / 2.0f);
    mat.m[0][0] = 1.0f / (aspect * tan_half_fovy);
    mat.m[1][1] = 1.0f / tan_half_fovy;
    mat.m[2][2] = -(far + near) / (far - near);
    mat.m[2][3] = 1.0f;
    mat.m[3][2] = -(2.0f * far * near) / (far - near);
    return mat;
}
