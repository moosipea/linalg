#ifndef LINALG_H
#define LINALG_H

#ifndef LINALG_PREFIX
#define LINALG_PREFIX linalg
#endif

#define __LINALG(prefix,name) prefix ## _ ## name
#define _LINALG(prefix,name) __LINALG(prefix,name)
#define LINALG(name) _LINALG(LINALG_PREFIX,name)

/*
* Structure definitions
*/

struct LINALG(Vec4)   { float x, y, z, w; };
struct LINALG(Mat4x4) { float m[4][4]; };

/*
* Vec4 functions
*/

struct LINALG(Vec4) LINALG(Vec4_create)(float x, float y, float z, float w);
struct LINALG(Vec4) LINALG(Vec4_add)(struct LINALG(Vec4) v0, struct LINALG(Vec4) v1);
struct LINALG(Vec4) LINALG(Vec4_sub)(struct LINALG(Vec4) v0, struct LINALG(Vec4) v1);
struct LINALG(Vec4) LINALG(Vec4_mul)(struct LINALG(Vec4) v, float k);
struct LINALG(Vec4) LINALG(Vec4_div)(struct LINALG(Vec4) v, float k);
struct LINALG(Vec4) LINALG(Vec4_matmul)(struct LINALG(Vec4) v, struct LINALG(Mat4x4) *mat); /* TODO */
float LINALG(Vec4_mag)(struct LINALG(Vec4) v);
struct LINALG(Vec4) LINALG(Vec4_norm)(struct LINALG(Vec4) v);
float LINALG(Vec4_dot)(struct LINALG(Vec4) v0, struct LINALG(Vec4) v1);

/*
* Mat4x4 functions TODO
*/

struct LINALG(Mat4x4) LINALG(Mat4x4_ident)(void);
void LINALG(Mat4x4_matmul)(struct LINALG(Mat4x4) *left, struct LINALG(Mat4x4) *right);
struct LINALG(Mat4x4) LINALG(Mat4x4_translation)(float dx, float dy, float dz);
struct LINALG(Mat4x4) LINALG(Mat4x4_scaling)(float sx, float sy, float sz);
struct LINALG(Mat4x4) LINALG(Mat4x4_rotation_x)(float r);
struct LINALG(Mat4x4) LINALG(Mat4x4_rotation_y)(float r);
struct LINALG(Mat4x4) LINALG(Mat4x4_rotation_z)(float r);
struct LINALG(Mat4x4) LINALG(Mat4x4_rotation)(float rx, float ry, float rz);
struct LINALG(Mat4x4) LINALG(Mat4x4_perspective)(float fovy, float aspect, float near, float far);


#endif /* LINALG_H */