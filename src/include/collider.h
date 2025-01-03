#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "include/math.h"

enum ColliderTag {
  COL_NONE = 0,
  COL_PLAYER,
};

struct Collider {
  ColliderTag tag;
  V2i position;
};

bool aabb_collision(Collider *c0, Collider *c1);

#endif/*_COLLIDER_H_*/
