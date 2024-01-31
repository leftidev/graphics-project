#pragma once

#include "linmath.h"
#include <cstdio>

typedef struct {
    vec3 position;
    vec2 textureCoordinate;
} Vertex;

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

/* mat4 */

typedef struct {
  float xx; float xy; float xz; float xw;
  float yx; float yy; float yz; float yw;
  float zx; float zy; float zz; float zw;
  float wx; float wy; float wz; float ww;
} mat4;

/* Matrix 4x4 */

inline void mat4_print(mat4& m) 
{
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.xx, m.xy, m.xz, m.xw);
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.yx, m.yy, m.yz, m.yw);
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.zx, m.zy, m.zz, m.zw);
  printf("|%4.2f, %4.2f, %4.2f, %4.2f|\n", m.wx, m.wy, m.wz, m.ww);
  
}

inline mat4 mat4_zero() 
{
  mat4 m;

  m.xx = 0.0f;
  m.xy = 0.0f;
  m.xz = 0.0f;
  m.xw = 0.0f;

  m.yx = 0.0f;
  m.yy = 0.0f;
  m.yz = 0.0f;
  m.yw = 0.0f;

  m.zx = 0.0f;
  m.zy = 0.0f;
  m.zz = 0.0f;
  m.zw = 0.0f;

  m.wx = 0.0f;
  m.wy = 0.0f;
  m.wz = 0.0f;
  m.ww = 0.0f;

  return m;
}

inline mat4 mat4_id() 
{
  mat4 m = mat4_zero();
  
  m.xx = 1.0f;
  m.yy = 1.0f;
  m.zz = 1.0f;
  m.ww = 1.0f;

  return m;
}

inline void mat4_translation(mat4& m, Vec3 v) 
{
  //mat4_id(m);
  m.wx = v.x;
  m.wy = v.y;
  m.wz = v.z;
}

inline void mat4_scale(mat4& m, Vec3 v) 
{
  //mat4_id(m);
  m.xx = v.x;
  m.yy = v.y;
  m.zz = v.z;
}

inline mat4 mat4_rotation_x(float a) 
{
  //mat4_zero(m);
  mat4 m = mat4_id();
  //m.xx = 1.0f;
  m.yy = cos(a);
  m.yz = -sin(a);
  m.zy = sin(a);
  m.zz = cos(a);
  //m.ww = 1.0f;
  return m;
}

inline mat4 mat4_rotation_y(float a) 
{
  mat4 m = mat4_id();

  m.xx = cos(a);
  m.xz = sin(a);
  m.zx = -sin(a);
  m.zz = cos(a);

  return m;
}

inline mat4 mat4_rotation_z(float a) 
{
  mat4 m = mat4_id();
  
  m.xx = cos(a);
  m.xy = -sin(a);
  m.yx = sin(a);
  m.yy = cos(a);

  return m;
}
/*
inline void mat4_rotation_axis_angle(mat4& m, Vec3 v, float angle) {

  mat4_id(m);

  float c = cos(angle);
  float s = sin(angle);
  float nc = 1 - c;
  
  m.xx = v.x * v.x * nc + c;
  m.xy = v.x * v.y * nc - v.z * s;
  m.xz = v.x * v.z * nc + v.y * s;
  
  m.yx = v.y * v.x * nc + v.z * s;
  m.yy = v.y * v.y * nc + c;
  m.yz = v.y * v.z * nc - v.x * s;
  
  m.zx = v.z * v.x * nc - v.y * s;
  m.zy = v.z * v.y * nc + v.x * s;
  m.zz = v.z * v.z * nc + c;
}
*/
inline mat4 mat4_mul_mat4(mat4 m1, mat4 m2) 
{
  mat4 m;

  m.xx = (m1.xx * m2.xx) + (m1.xy * m2.yx) + (m1.xz * m2.zx) + (m1.xw * m2.wx);
  m.xy = (m1.xx * m2.xy) + (m1.xy * m2.yy) + (m1.xz * m2.zy) + (m1.xw * m2.wy);
  m.xz = (m1.xx * m2.xz) + (m1.xy * m2.yz) + (m1.xz * m2.zz) + (m1.xw * m2.wz);
  m.xw = (m1.xx * m2.xw) + (m1.xy * m2.yw) + (m1.xz * m2.zw) + (m1.xw * m2.ww);
  
  m.yx = (m1.yx * m2.xx) + (m1.yy * m2.yx) + (m1.yz * m2.zx) + (m1.yw * m2.wx);
  m.yy = (m1.yx * m2.xy) + (m1.yy * m2.yy) + (m1.yz * m2.zy) + (m1.yw * m2.wy);
  m.yz = (m1.yx * m2.xz) + (m1.yy * m2.yz) + (m1.yz * m2.zz) + (m1.yw * m2.wz);
  m.yw = (m1.yx * m2.xw) + (m1.yy * m2.yw) + (m1.yz * m2.zw) + (m1.yw * m2.ww);
 
  m.zx = (m1.zx * m2.xx) + (m1.zy * m2.yx) + (m1.zz * m2.zx) + (m1.zw * m2.wx);
  m.zy = (m1.zx * m2.xy) + (m1.zy * m2.yy) + (m1.zz * m2.zy) + (m1.zw * m2.wy);
  m.zz = (m1.zx * m2.xz) + (m1.zy * m2.yz) + (m1.zz * m2.zz) + (m1.zw * m2.wz);
  m.zw = (m1.zx * m2.xw) + (m1.zy * m2.yw) + (m1.zz * m2.zw) + (m1.zw * m2.ww);
  
  m.wx = (m1.wx * m2.xx) + (m1.wy * m2.yx) + (m1.wz * m2.zx) + (m1.ww * m2.wx);
  m.wy = (m1.wx * m2.xy) + (m1.wy * m2.yy) + (m1.wz * m2.zy) + (m1.ww * m2.wy);
  m.wz = (m1.wx * m2.xz) + (m1.wy * m2.yz) + (m1.wz * m2.zz) + (m1.ww * m2.wz);
  m.ww = (m1.wx * m2.xw) + (m1.wy * m2.yw) + (m1.wz * m2.zw) + (m1.ww * m2.ww);

  return m;
}
/*
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
*/

inline void mat4_perspective_two(mat4& m, float y_fov, float n, float f, float aspect)
{
  /* NOTE: Degrees are an unhandy unit to work with.
    * linmath.h uses radians for everything! */
  float const a = 1.f / tanf(y_fov / 2.f);

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
}


