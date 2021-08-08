#ifndef __MATH_VEC_H__
#define __MATH_VEC_H__

#include "engine/math/types.h"

/**********************************
 * Vec2
 **********************************/

#define VEC2_ONE (vec2_t){{1.0f, 1.0f}}

void  vec2_zero(vec2_t out);
void  vec2_copy(vec2_t out, const vec2_t v);

void  vec2_add(vec2_t out, const vec2_t v1, const vec2_t v2);
void  vec2_sub(vec2_t out, const vec2_t v1, const vec2_t v2);
void  vec2_mul(vec2_t out, const vec2_t v1, const vec2_t v2);
void  vec2_div(vec2_t out, const vec2_t v1, const vec2_t v2);

void  vec2_add_s(vec2_t out, const vec2_t v1, float s);
void  vec2_sub_s(vec2_t out, const vec2_t v1, float s);
void  vec2_mul_s(vec2_t out, const vec2_t v1, float s);
void  vec2_div_s(vec2_t out, const vec2_t v1, float s);

float vec2_mag2(const vec2_t v);
float vec2_mag(const vec2_t v);
float vec2_dot(const vec2_t v1, const vec2_t v2);

float vec2_minval(const vec2_t v);
float vec2_maxval(const vec2_t v);

void  vec2_min(vec2_t out, const vec2_t v1, const vec2_t v2);
void  vec2_max(vec2_t out, const vec2_t v1, const vec2_t v2);

void  vec2_negate(vec2_t out);
void  vec2_rotate(vec2_t out, const vec2_t v, float angle);

void  vec2_norm(vec2_t out);
void  vec2_norm_to(vec2_t out, const vec2_t v);

/**********************************
 * Vec3
 **********************************/

#define VEC3_ONE (vec3_t){{1.0f, 1.0f, 1.0f}}
#define VEC3_X   (vec3_t){{1.0f, 0.0f, 0.0f}}
#define VEC3_Y   (vec3_t){{0.0f, 1.0f, 0.0f}}
#define VEC3_Z   (vec3_t){{0.0f, 0.0f, 1.0f}}

void  vec3_zero(vec3_t out);
void  vec3_copy(vec3_t out, const vec3_t v);

void  vec3_add(vec3_t out, const vec3_t v1, const vec3_t v2);
void  vec3_sub(vec3_t out, const vec3_t v1, const vec3_t v2);
void  vec3_mul(vec3_t out, const vec3_t v1, const vec3_t v2);
void  vec3_mul(vec3_t out, const vec3_t v1, const vec3_t v2);

void  vec3_add_s(vec3_t out, const vec3_t v1, float s);
void  vec3_sub_s(vec3_t out, const vec3_t v1, float s);
void  vec3_mul_s(vec3_t out, const vec3_t v1, float s);
void  vec3_div_s(vec3_t out, const vec3_t v1, float s);

float vec3_mag2(const vec3_t v);
float vec3_mag(const vec3_t v);
float vec3_dot(const vec3_t v1, const vec3_t v2);

void  vec3_min(vec3_t out, const vec3_t v1, const vec3_t v2);
void  vec3_max(vec3_t out, const vec3_t v1, const vec3_t v2);

float vec3_minval(const vec3_t v);
float vec3_maxval(const vec3_t v);

void  vec3_negate(vec3_t out);
void  vec3_cross(vec3_t out, const vec3_t v1, const vec3_t v2);

void  vec3_norm(vec3_t out);
void  vec3_norm_to(vec3_t out, const vec3_t v);

/**********************************
 * Vec4
 **********************************/

#define VEC4_ONE (vec4_t){{1.0f, 1.0f, 1.0f, 1.0f}}
#define VEC4_X   (vec4_t){{1.0f, 0.0f, 0.0f, 0.0f}}
#define VEC4_Y   (vec4_t){{0.0f, 1.0f, 0.0f, 0.0f}}
#define VEC4_Z   (vec4_t){{0.0f, 0.0f, 1.0f, 0.0f}}
#define VEC4_W   (vec4_t){{0.0f, 0.0f, 0.0f, 1.0f}}

void  vec4_zero(vec4_t out);
void  vec4_copy(vec4_t out, const vec4_t v);

void  vec4_add(vec4_t out, const vec4_t v1, const vec4_t v2);
void  vec4_sub(vec4_t out, const vec4_t v1, const vec4_t v2);
void  vec4_mul(vec4_t out, const vec4_t v1, const vec4_t v2);
void  vec4_div(vec4_t out, const vec4_t v1, const vec4_t v2);

void  vec4_add_s(vec4_t out, const vec4_t v1, float s);
void  vec4_sub_s(vec4_t out, const vec4_t v1, float s);
void  vec4_mul_s(vec4_t out, const vec4_t v1, float s);
void  vec4_div_s(vec4_t out, const vec4_t v1, float s);

float vec4_mag2(const vec4_t v);
float vec4_mag(const vec4_t v);
float vec4_dot(const vec4_t v1, const vec4_t v2);

float vec4_minval(const vec4_t v);
float vec4_maxval(const vec4_t v);

void  vec4_negate(vec4_t out);


#endif /* __MATH_VEC_H__ */
