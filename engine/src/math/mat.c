#include "engine/math/mat.h"
#include "engine/math/vec.h" /* vec*_copy */

#include <math.h> /* trig functions */
#include <string.h> /* memcpy, memset */

/**********************************
 * Mat3
 **********************************/

void
mat3_identity(mat3_t out)
{
    mat3_copy(out, MAT3_IDENTITY);
}

void
mat3_zero(mat3_t out)
{
    memset(out, 0, 9 * sizeof(*out));
}

void
mat3_copy(mat3_t out, const mat3_t m)
{
    memcpy(out, m, 9 * sizeof(*out));
}

void
mat3_add(mat3_t out, const mat3_t m1, const mat3_t m2)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            out[i][j] = m1[i][j] + m2[i][j];
}

void
mat3_sub(mat3_t out, const mat3_t m1, const mat3_t m2)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            out[i][j] = m1[i][j] - m2[i][j];
}

void
mat3_mul(mat3_t out, const mat3_t m1, const mat3_t m2)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            out[i][j] = m1[i][j] * m2[i][j];
}

void
mat3_mulv(vec3_t out, const mat3_t m, const vec3_t v)
{
    out[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2];
    out[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2];
    out[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2];
}

void
mat3_translate(mat3_t out, const mat3_t m, const vec2_t v)
{
    UNUSED(out); UNUSED(m); UNUSED(v);
}

void
mat3_rotate(mat3_t out, const mat3_t m, float angle)
{
    UNUSED(out); UNUSED(m); UNUSED(angle);
}

void
mat3_scale(mat3_t out, const mat3_t m, const vec2_t scale)
{
    UNUSED(out); UNUSED(m); UNUSED(scale);
}

/**********************************
 * Mat4
 **********************************/

void
mat4_identity(mat4_t out)
{
    mat4_copy(out, MAT4_IDENTITY);
}

void
mat4_zero(mat4_t out)
{
    mat4_copy(out, (mat4_t){0});
}

void
mat4_copy(mat4_t out, const mat4_t m)
{
    memcpy(out, m, 16 * sizeof(*out));
}

void
mat4_add(mat4_t out, const mat4_t m1, const mat4_t m2)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            out[i][j] = m1[i][j] + m2[i][j];
}

void
mat4_sub(mat4_t out, const mat4_t m1, const mat4_t m2)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            out[i][j] = m1[i][j] - m2[i][j];
}

void
mat4_mul(mat4_t out, const mat4_t m1, const mat4_t m2)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            out[i][j] = m1[i][j] * m2[i][j];
}

void
mat4_mulv(mat4_t out, const mat4_t m, const vec4_t v)
{
    UNUSED(out); UNUSED(m); UNUSED(v);
}

void
mat4_mulv3(mat4_t out, const mat4_t m, const vec3_t v)
{
    UNUSED(out); UNUSED(m); UNUSED(v);
}

void
mat4_translate(mat4_t out, const mat4_t m, const vec3_t v)
{
    mat4_identity(out);
    vec3_copy(out[3], v);
    mat4_mul(out, m, out);
}

/* https://neutrium.net/mathematics/basics-of-affine-transformation/ */
void
mat4_rotate(mat4_t out, const mat4_t m, const vec3_t axis, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    vec3_t an;
    vec3_norm_to(an, axis);

    vec3_t vs;
    vec3_mul_s(vs, an, s);

    mat4_t rot = {0};
    rot[0][0] += c;
    rot[0][1] += vs[2];
    rot[0][2] -= vs[1];
    rot[1][0] -= vs[2];
    rot[1][1] += c;
    rot[1][2] += vs[0];
    rot[2][0] += vs[1];
    rot[2][1] -= vs[0];
    rot[2][2] += c;

    rot[0][3] = rot[1][3] = rot[2][3] = rot[3][0] = rot[3][1] = rot[3][2] = 0.0f;
    rot[3][3] = 1.0f;

    mat4_mul(out, m, rot);
}

void
mat4_scale(mat4_t out, const mat4_t m, const vec3_t scale)
{
    vec4_mul_s(out[0], m[0], scale[0]);
    vec4_mul_s(out[1], m[1], scale[1]);
    vec4_mul_s(out[2], m[2], scale[2]);
    vec4_copy(out[3], m[3]);
}

void
mat4_lookat(mat4_t out, const vec3_t eye, const vec3_t center, const vec3_t up)
{
    UNUSED(out); UNUSED(eye); UNUSED(center); UNUSED(up);
}

void
mat4_perspective(mat4_t out,
                 float fov_deg,
                 float aspect,
                 float near,
                 float far)
{
    UNUSED(out); UNUSED(fov_deg); UNUSED(aspect); UNUSED(near); UNUSED(far);
}

void
mat4_ortho(mat4_t out, float l, float r, float t, float b, float n, float f)
{
    UNUSED(out); UNUSED(l); UNUSED(r); UNUSED(t); UNUSED(b); UNUSED(n); UNUSED(f);
}

void
mat4_ortho_aabb(mat4_t out, const aabb3_t box)
{
    UNUSED(out); UNUSED(box);
}
