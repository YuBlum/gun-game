#ifndef _MOVER_H_
#define _MOVER_H_

#include "include/math.h"
#include "include/collider.h"

struct Mover {
  V2f velocity;
  V2f remainder;
  f32 weight;
};

struct UpdateMoverResult {
  bool collided_x;
  bool collided_y;
};

UpdateMoverResult update_mover(Mover *mover, Collider *collider, f32 dt, bool use_gravity = true, bool resolve_collision = true);
bool is_on_ground(V2i position);

#endif/*_MOVER_H_*/
