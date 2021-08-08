#ifndef __MATH_MAT_H__
#define __MATH_MAT_H__

#include "engine/math/types.h"

/**********************************
 * Mat3
 **********************************/

#define MAT3_IDENTITY       \
    (mat3_t){               \
        {1.0f, 0.0f, 0.0f}, \
        {0.0f, 1.0f, 0.0f}, \
        {0.0f, 0.0f, 1.0f}  \
    }

void mat3_identity(mat3_t out);
void mat3_zero(mat3_t out);
void mat3_copy(mat3_t out, const mat3_t m);

void mat3_add(mat3_t out, const mat3_t m1, const mat3_t m2);
void mat3_sub(mat3_t out, const mat3_t m1, const mat3_t m2);
void mat3_mul(mat3_t out, const mat3_t m1, const mat3_t m2);

void mat3_mul_v(vec3_t out, const mat3_t m, const vec3_t v);

void mat3_translate(mat3_t out, const mat3_t m, const vec2_t v);
void mat3_rotate(mat3_t out, const mat3_t m, float angle);
void mat3_scale(mat3_t out, const mat3_t m, const vec2_t v);

/**********************************
 * Mat4
 **********************************/

#define MAT4_IDENTITY               \
    (mat4_t){                       \
        {1.0f, 0.0f, 0.0f, 0.0f},   \
        {0.0f, 1.0f, 0.0f, 0.0f},   \
        {0.0f, 0.0f, 1.0f, 0.0f},   \
        {0.0f, 0.0f, 0.0f, 1.0f}    \
    }

void mat4_identity(mat4_t out);
void mat4_zero(mat4_t out);
void mat4_copy(mat4_t out, const mat4_t m);

void mat4_add(mat4_t out, const mat4_t m1, const mat4_t m2);
void mat4_sub(mat4_t out, const mat4_t m1, const mat4_t m2);
void mat4_mul(mat4_t out, const mat4_t m1, const mat4_t m2);

void mat4_mul_v(mat4_t out, const mat4_t m, const vec4_t v);
void mat4_mul_v3(mat4_t out, const mat4_t m, const vec3_t v);

void mat4_translate(mat4_t out, const mat4_t mat, const vec3_t translation);
void mat4_rotate(mat4_t out, const mat4_t mat, const vec3_t axis, float angle);
void mat4_scale(mat4_t out, const mat4_t mat, const vec3_t scale);

void mat4_lookat(mat4_t out, const vec3_t eye, const vec3_t center, const vec3_t up);
void mat4_perspective(mat4_t out, float fov_deg, float aspect, float near, float far);
void mat4_ortho(mat4_t out, float l, float r, float t, float b, float n, float f);

#endif /* __MATH_MAT_H__ */
