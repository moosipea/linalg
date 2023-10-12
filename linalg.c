#include "math.h"
#include "linalg.h"

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

struct linalg_Vec4 linalg_Vec4_sub(struct linalg_Vec4 v0,
                                   struct linalg_Vec4 v1) {
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

void linalg_Mat4x4_matmul(struct linalg_Mat4x4 *with,
                          struct linalg_Mat4x4 *mat) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      mat->m[y][x] =
          mat->m[y][0] * with->m[0][x] + mat->m[y][1] * with->m[1][x] +
          mat->m[y][2] * with->m[2][x] + mat->m[y][3] * with->m[3][x];
    }
  }
}

struct linalg_Mat4x4 linalg_Mat4x4_translation(float dx, float dy, float dz) {
  struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
  mat.m[0][3] = dx;
  mat.m[1][3] = dx;
  mat.m[2][3] = dx;
  return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_scaling(float sx, float sy, float sz) {
  struct linalg_Mat4x4 mat = linalg_Mat4x4_ident();
  mat.m[0][0] = sx;
  mat.m[1][1] = sx;
  mat.m[2][2] = sx;
  return mat;
}

struct linalg_Mat4x4 linalg_Mat4x4_rotation_x(float r);
struct linalg_Mat4x4 linalg_Mat4x4_rotation_y(float r);
struct linalg_Mat4x4 linalg_Mat4x4_rotation_z(float r);

struct linalg_Mat4x4 linalg_Mat4x4_rotation(float rx, float ry, float rz) {
  struct linalg_Mat4x4 mat_z = linalg_Mat4x4_rotation_z(rz);
  struct linalg_Mat4x4 mat_x = linalg_Mat4x4_rotation_x(rx);
  struct linalg_Mat4x4 mat_y = linalg_Mat4x4_rotation_y(ry);
  linalg_Mat4x4_matmul(&mat_x, &mat_z);
  linalg_Mat4x4_matmul(&mat_y, &mat_z);
  return mat_z;
}

struct linalg_Mat4x4 linalg_Mat4x4_perspective(float fovy, float aspect,
                                               float near, float far);