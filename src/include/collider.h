#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "include/math.h"

struct Collider {
  V2i position;
  V2i size;
};

bool aabb_collision(Collider *c0, Collider *c1);
#if DEBUG
void debug_render_collider(Collider *c);
#endif

#endif/*_COLLIDER_H_*/
