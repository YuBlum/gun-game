#ifndef _MOVER_H_
#define _MOVER_H_

#include "include/math.h"

struct Mover {
  V2i position;
  V2f velocity;
  V2f remainder;
};

void update_mover(Mover *mover, f32 dt);

#endif/*_MOVER_H_*/
