#include "include/mover.h"
#include "include/math.h"

void
update_mover(Mover *mover, f32 dt) {
  mover->remainder += mover->velocity * dt;
  if (ABS(mover->remainder.x) >= 1) {
    mover->position.x += i32(mover->remainder.x);
    mover->remainder.x -= i32(mover->remainder.x);
  }
  if (ABS(mover->remainder.y) >= 1) {
    mover->position.y += i32(mover->remainder.y);
    mover->remainder.y -= i32(mover->remainder.y);
  }
}
