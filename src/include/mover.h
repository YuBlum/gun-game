#ifndef _MOVER_H_
#define _MOVER_H_

#include "include/math.h"
#include "include/collider.h"

struct Mover {
  Collider collider;
  V2f velocity;
  V2f remainder;
  f32 weight;
  bool on_ground;
  bool has_gravity;
};

void update_mover(Mover *mover, f32 dt);

#endif/*_MOVER_H_*/
