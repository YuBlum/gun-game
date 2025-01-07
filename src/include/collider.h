#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "include/math.h"

#pragma warning(disable : 4201)
struct Collider {
  union {
    struct { V2i position, size; };
    struct { i32 x, y, w, h; };
  };
};

bool collider_on_collider(Collider *c0, Collider *c1);
Direction collider_outside_of_screen(Collider *c);
bool is_on_ground(Collider *collider);
#if DEBUG
void debug_render_collider(Collider *c);
#endif

#endif/*_COLLIDER_H_*/
