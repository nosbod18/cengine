#include "engine/math/vec.h"
#include "engine/math/types.h"

#include <math.h>

/**********************************
 * Vec2
 **********************************/

void
vec2_zero(vec2_t out)
{
    out[0] = out[1] = 0.0f;
}

void
vec2_copy(vec2_t out, const vec2_t v)
{
    out[0] = v[0];
    out[1] = v[1];
}

void
vec2_add(vec2_t out, const vec2_t v1, const vec2_t v2)
{
    out[0] = v1[0] + v2[0];
    out[1] = v1[1] + v2[1];
}

void
vec2_sub(vec2_t out, const vec2_t v1, const vec2_t v2)
{
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
}

void
vec2_mul(vec2_t out, const vec2_t v1, const vec2_t v2)
{
    out[0] = v1[0] * v2[0];
    out[1] = v1[1] * v2[1];
}

void
vec2_div(vec2_t out, const vec2_t v1, const vec2_t v2)
{
    out[0] = v1[0] / v2[0];
    out[1] = v1[1] / v2[1];
}

void
vec2_add_s(vec2_t out, const vec2_t v1, float s)
{
    out[0] = v1[0] + s;
    out[1] = v1[1] + s;
}

void
vec2_sub_s(vec2_t out, const vec2_t v1, float s)
{
    out[0] = v1[0] - s;
    out[1] = v1[1] - s;
}

void
vec2_mul_s(vec2_t out, const vec2_t v1, float s)
{
    out[0] = v1[0] * s;
    out[1] = v1[1] * s;
}

void
vec2_div_s(vec2_t out, const vec2_t v1, float s)
{
    out[0] = v1[0] / s;
    out[1] = v1[1] / s;
}

float
vec2_mag2(const vec2_t v)
{
    return v[0] * v[0] + v[1] * v[1];
}

float
vec2_mag(const vec2_t v)
{
    return sqrtf(vec2_mag2(v));
}

float
vec2_dot(const vec2_t v1, const vec2_t v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1];
}

float
vec2_minval(const vec2_t v)
{
    return MIN(v[0], v[1]);
}

float
vec2_maxval(const vec2_t v)
{
    return MAX(v[0], v[1]);
}

void
vec2_min(vec2_t out, const vec2_t v1, const vec2_t v2)
{
    out[0] = MIN(v1[0], v2[0]);
    out[1] = MIN(v1[1], v2[1]);
}

void
vec2_max(vec2_t out, const vec2_t v1, const vec2_t v2)
{
    out[0] = MAX(v1[0], v2[0]);
    out[0] = MAX(v1[1], v2[1]);
}

void
vec2_negate(vec2_t out)
{
    out[0] = -out[0];
    out[1] = -out[1];
}

void
vec2_rotate(vec2_t out, const vec2_t v, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    out[0] = c * v[0] - s * v[1];
    out[1] = s * v[0] + c * v[1];
}

void
vec2_norm(vec2_t out)
{
    vec2_div_s(out, out, vec2_mag(out));
}

void
vec2_norm_to(vec2_t out, const vec2_t v)
{
    vec2_div_s(out, v, vec2_mag(v));
}

/**********************************
 * Vec3
 **********************************/

void
vec3_zero(vec3_t out)
{
    out[0] = out[1] = out[2] = 0.0f;
}

void
vec3_copy(vec3_t out, const vec3_t v)
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
}

void
vec3_add(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = v1[0] + v2[0];
    out[1] = v1[1] + v2[1];
    out[2] = v1[2] + v2[2];
}

void
vec3_sub(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
}

void
vec3_mul(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = v1[0] * v2[0];
    out[1] = v1[1] * v2[1];
    out[2] = v1[2] * v2[2];
}

void
vec3_div(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = v1[0] / v2[0];
    out[1] = v1[1] / v2[1];
    out[2] = v1[2] / v2[2];
}

void
vec3_add_s(vec3_t out, const vec3_t v1, float s)
{
    out[0] = v1[0] + s;
    out[1] = v1[1] + s;
    out[2] = v1[2] + s;
}

void
vec3_sub_s(vec3_t out, const vec3_t v1, float s)
{
    out[0] = v1[0] - s;
    out[1] = v1[1] - s;
    out[2] = v1[2] - s;
}

void
vec3_mul_s(vec3_t out, const vec3_t v1, float s)
{
    out[0] = v1[0] * s;
    out[1] = v1[1] * s;
    out[2] = v1[2] * s;
}

void
vec3_div_s(vec3_t out, const vec3_t v1, float s)
{
    out[0] = v1[0] / s;
    out[1] = v1[1] / s;
    out[2] = v1[2] / s;
}

float
vec3_mag2(const vec3_t v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

float
vec3_mag(const vec3_t v)
{
    return sqrt(vec3_mag2(v));
}

float
vec3_dot(const vec3_t v1, const vec3_t v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float
vec3_minval(const vec3_t v)
{
    return MIN(v[0], MIN(v[1], v[2]));
}

float
vec3_maxval(const vec3_t v)
{
    return MAX(v[0], MAX(v[1], v[2]));
}

void
vec3_min(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = MIN(v1[0], v2[0]);
    out[1] = MIN(v1[1], v2[1]);
    out[2] = MIN(v1[2], v2[2]);
}

void
vec3_max(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = MAX(v1[0], v2[0]);
    out[1] = MAX(v1[1], v2[1]);
    out[2] = MAX(v1[2], v2[2]);
}

void
vec3_negate(vec3_t out)
{
    out[0] = -out[0];
    out[1] = -out[1];
    out[2] = -out[2];
}

void
vec3_cross(vec3_t out, const vec3_t v1, const vec3_t v2)
{
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void
vec3_norm(vec3_t out)
{
    vec3_div_s(out, out, vec3_mag(out));
}

void
vec3_norm_to(vec3_t out, const vec3_t v)
{
    vec3_div_s(out, v, vec3_mag(v));
}

/**********************************
 * Vec4
 **********************************/

void
vec4_copy(vec4_t out, const vec4_t v)
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
}

void
vec4_add(vec4_t out, const vec4_t v1, const vec4_t v2)
{
    out[0] = v1[0] + v2[0];
    out[1] = v1[1] + v2[1];
    out[2] = v1[2] + v2[2];
    out[3] = v1[3] + v2[3];
}

void
vec4_sub(vec4_t out, const vec4_t v1, const vec4_t v2)
{
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
    out[3] = v1[3] - v2[3];
}

void
vec4_mul(vec4_t out, const vec4_t v1, const vec4_t v2)
{
    out[0] = v1[0] * v2[0];
    out[1] = v1[1] * v2[1];
    out[2] = v1[2] * v2[2];
    out[3] = v1[3] * v2[3];
}

void
vec4_div(vec4_t out, const vec4_t v1, const vec4_t v2)
{
    out[0] = v1[0] / v2[0];
    out[1] = v1[1] / v2[1];
    out[2] = v1[2] / v2[2];
    out[3] = v1[3] / v2[3];
}

void
vec4_add_s(vec4_t out, const vec4_t v1, float s)
{
    out[0] = v1[0] + s;
    out[1] = v1[1] + s;
    out[2] = v1[2] + s;
    out[3] = v1[3] + s;
}

void
vec4_sub_s(vec4_t out, const vec4_t v1, float s)
{
    out[0] = v1[0] - s;
    out[1] = v1[1] - s;
    out[2] = v1[2] - s;
    out[3] = v1[3] - s;
}

void
vec4_mul_s(vec4_t out, const vec4_t v1, float s)
{
    out[0] = v1[0] * s;
    out[1] = v1[1] * s;
    out[2] = v1[2] * s;
    out[3] = v1[3] * s;
}

void
vec4_div_s(vec4_t out, const vec4_t v1, float s)
{
    out[0] = v1[0] / s;
    out[1] = v1[1] / s;
    out[2] = v1[2] / s;
    out[3] = v1[3] / s;
}

float
vec4_minval(const vec4_t v)
{
    return MIN(v[0], MIN(v[1], MIN(v[2], v[3])));
}

float
vec4_maxval(const vec4_t v)
{
    return MAX(v[0], MAX(v[1], MAX(v[2], v[3])));
}

void
vec4_negate(vec4_t out)
{
    out[0] = -out[0];
    out[1] = -out[1];
    out[2] = -out[2];
    out[3] = -out[3];
}

