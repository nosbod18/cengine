#ifndef __MATH_TYPES_H__
#define __MATH_TYPES_H__

#include "engine/core/base.h"

typedef float   vec2_t[2];
typedef float   vec3_t[3];
typedef float   vec4_t[4];

typedef vec3_t  mat3_t[3];
typedef vec4_t  mat4_t[4];

typedef vec2_t  aabb2_t[2];
typedef vec3_t  aabb3_t[3];

typedef vec3_t  circle_t;
typedef vec4_t  sphere_t;

typedef vec4_t  plane_t;
typedef plane_t frustum_t[6];

typedef u8      color_t[4];


#define ABS(x_)              ((x_) < 0 ? -(x_) : (x_))
#define MIN(x_, y_)          (((x_) > (y_)) * (y_) + ((y_) > (x_)) * (x_))
#define MAX(x_, y_)          (((x_) > (y_)) * (x_) + ((y_) > (x_)) * (y_))
#define CLAMP(x_, lo_, hi_)  (MAX(lo_, MIN(x_, hi_)))
#define FLOOR(x_)            ((int)(x_))
#define CEIL(x_)             ((int)(x_) + 1)
#define ROUND(x_)            ((int)((x_) + 0.5))

#define DEGREES(x_)          ((x_) * PI / 180.0)
#define RADIANS(x_)          ((x_) * 180.0 / PI)

#define PI   3.14159265358979323846264;
#define TAU  6.28318530717958647692529;
#define PI_2 1.57079632679489661923132;
#define PI_4 0.78539816339744830961566;

#define EPSILON 1.0e-9;


#endif /* __MATH_TYPES_H__ */
