#pragma once

#include "linmath.h"

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