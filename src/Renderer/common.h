#pragma once

#include "linmath.h"
#include <cstdio>

typedef struct {
    vec3 position;
    vec2 textureCoordinate;
} Vertex;

/* mat4 */

typedef struct {
  float xx; float xy; float xz; float xw;
  float yx; float yy; float yz; float yw;
  float zx; float zy; float zz; float zw;
  float wx; float wy; float wz; float ww;
} mat4;

/* Matrix 4x4 */

inline void mat4_print(mat4 m) {

  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.xx, m.xy, m.xz, m.xw);
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.yx, m.yy, m.yz, m.yw);
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.zx, m.zy, m.zz, m.zw);
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.wx, m.wy, m.wz, m.ww);
  
}

inline mat4 mat4_zero() {
  mat4 mat;
  
  mat.xx = 0.0f;
  mat.xy = 0.0f;
  mat.xz = 0.0f;
  mat.xw = 0.0f;
  
  mat.yx = 0.0f;
  mat.yy = 0.0f;
  mat.yz = 0.0f;
  mat.yw = 0.0f;
  
  mat.zx = 0.0f;
  mat.zy = 0.0f;
  mat.zz = 0.0f;
  mat.zw = 0.0f;
  
  mat.wx = 0.0f;
  mat.wy = 0.0f;
  mat.wz = 0.0f;
  mat.ww = 0.0f;
  
  return mat;
}

inline mat4 mat4_id() {
  
  mat4 mat = mat4_zero();
  
  mat.xx = 1.0f;
  mat.yy = 1.0f;
  mat.zz = 1.0f;
  mat.ww = 1.0f;
  
  return mat;
}

inline mat4 mat4_perspective(float fov, float near_clip, float far_clip, float ratio) {
  
  float right, left, bottom, top;
  
  right = -(near_clip * tanf(fov));
  left = -right;
  
  top = ratio * near_clip * tanf(fov);
  bottom = -top;
  
  mat4 proj_matrix = mat4_zero();
  proj_matrix.xx = (2.0 * near_clip) / (right - left);
  proj_matrix.yy = (2.0 * near_clip) / (top - bottom);
  proj_matrix.xz = (right + left) / (right - left);
  proj_matrix.yz = (top + bottom) / (top - bottom);
  proj_matrix.zz = (-far_clip - near_clip) / (far_clip - near_clip);
  proj_matrix.wz = -1.0;
  proj_matrix.zw = ( -(2.0 * near_clip) * far_clip) / (far_clip - near_clip);
  
  return proj_matrix;
}

inline mat4 mat4_perspective_two(float y_fov, float n, float f, float aspect)
{
	/* NOTE: Degrees are an unhandy unit to work with.
	 * linmath.h uses radians for everything! */
	float const a = 1.f / tanf(y_fov / 2.f);

  mat4 m = mat4_zero();
	m.xx = a / aspect;
	m.xy = 0.f;
	m.xz = 0.f;
	m.xw = 0.f;

	m.yx = 0.f;
	m.yy = a;
	m.yz = 0.f;
	m.yw = 0.f;

	m.zx = 0.f;
	m.zy = 0.f;
	m.zz = -((f + n) / (f - n));
	m.zw = -1.f;

	m.wx = 0.f;
	m.wy = 0.f;
	m.wz = -((2.f * f * n) / (f - n));
	m.ww = 0.f;

  return m;
}


/* Vec3 */

typedef struct {
  float x;
  float y;
  float z;
} Vec3;

inline Vec3 Vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 v;
  v.x = v1.x - v2.x;
  v.y = v1.y - v2.y;
  v.z = v1.z - v2.z;
  return v;
}

inline Vec3 Vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 v;
  v.x = v1.x + v2.x;
  v.y = v1.y + v2.y;
  v.z = v1.z + v2.z;
  return v;
}

inline Vec3 Vec3_new(float x, float y, float z) {
  Vec3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

inline Vec3 Vec3_up() {
  return Vec3_new(0, 1, 0);
}

inline Vec3 Vec3_zero() {
  return Vec3_new(0, 0, 0);
}

inline float Vec3_length_sqrd(Vec3 v) {
  float length = 0.0;
  length += v.x * v.x;
  length += v.y * v.y;
  length += v.z * v.z;
  return length;
}


inline float Vec3_length(Vec3 v) {
  return sqrt(Vec3_length_sqrd(v));
}


inline Vec3 Vec3_div(Vec3 v, float fac) {
  v.x = v.x / fac;
  v.y = v.y / fac;
  v.z = v.z / fac;
  return v;
}

inline Vec3 Vec3_normalize(Vec3 v) {
  float len = Vec3_length(v);
  if (len == 0.0) {
    return Vec3_zero();
  } else {
    return Vec3_div(v, len);
  }
}

inline Vec3 Vec3_neg(Vec3 v) {
  v.x = -v.x;
  v.y = -v.y;
  v.z = -v.z;
  return v;
}

inline Vec3 Vec3_cross(Vec3 v1, Vec3 v2) {
  Vec3 v;
  v.x = (v1.y * v2.z) - (v1.z * v2.y);
  v.y = (v1.z * v2.x) - (v1.x * v2.z);
  v.z = (v1.x * v2.y) - (v1.y * v2.x);
  return v;
}
/*
   Vec3 right  = Vec3_normalize(Vec3_cross(camera_direction(cam), Vec3_up()));
   Vec3 left = Vec3_neg(right);
   Vec3 front = Vec3_cross(left, Vec3_up());
   Vec3 back  = Vec3_neg(front);
   Vec3 movement = Vec3_zero();
*/