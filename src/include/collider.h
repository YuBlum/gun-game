#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "include/math.h"

enum ColliderTag {
  COL_NONE = 0,
  COL_PLAYER,
};

struct Collider {
  ColliderTag tag;
  V2i size;
}

bool aabb_collision(V2i p0, Collider *c0, V2i p1, Collider *c1);

#endif/*_COLLIDER_H_*/
