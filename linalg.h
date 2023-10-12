#ifndef LINALG_H
#define LINALG_H

/*
 * Structure definitions
 */

struct linalg_Vec4 {
    float x, y, z, w;
};
struct linalg_Mat4x4 {
    float m[4][4];
};

/*
 * Vec4 functions
 */

struct linalg_Vec4 linalg_Vec4_create(float x, float y, float z, float w);
struct linalg_Vec4 linalg_Vec4_add(struct linalg_Vec4 v0, struct linalg_Vec4 v1);
struct linalg_Vec4 linalg_Vec4_sub(struct linalg_Vec4 v0, struct linalg_Vec4 v1);
struct linalg_Vec4 linalg_Vec4_mul(struct linalg_Vec4 v, float k);
struct linalg_Vec4 linalg_Vec4_div(struct linalg_Vec4 v, float k);
struct linalg_Vec4 linalg_Vec4_matmul(struct linalg_Vec4 v, struct linalg_Mat4x4 *mat); /* TODO */
float linalg_Vec4_mag(struct linalg_Vec4 v);
struct linalg_Vec4 linalg_Vec4_norm(struct linalg_Vec4 v);
float linalg_Vec4_dot(struct linalg_Vec4 v0, struct linalg_Vec4 v1);

/*
 * Mat4x4 functions TODO
 */

struct linalg_Mat4x4 linalg_Mat4x4_ident(void);
void linalg_Mat4x4_matmul(struct linalg_Mat4x4 *left, struct linalg_Mat4x4 *right);
struct linalg_Mat4x4 linalg_Mat4x4_translation(float dx, float dy, float dz);
struct linalg_Mat4x4 linalg_Mat4x4_scaling(float sx, float sy, float sz);
struct linalg_Mat4x4 linalg_Mat4x4_rotation_x(float r);
struct linalg_Mat4x4 linalg_Mat4x4_rotation_y(float r);
struct linalg_Mat4x4 linalg_Mat4x4_rotation_z(float r);
struct linalg_Mat4x4 linalg_Mat4x4_rotation(float rx, float ry, float rz);
struct linalg_Mat4x4 linalg_Mat4x4_perspective(float fovy, float aspect, float near, float far);

#endif /* LINALG_H */