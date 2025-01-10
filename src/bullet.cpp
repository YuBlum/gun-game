#include "include/bullet.h"
#include "include/core.h"
#include "include/debug.h"
#include "include/renderer.h"

void
bullet_update(Entities *e, f32 dt) {
  Bullet *b = &e->bullet;
  if (!b->alive) return;
  /* move bullets */
  UpdateMoverResult mover_result = update_mover(&b->mover, &b->collider, dt, false, false);
  if (mover_result.collided_x || mover_result.collided_y || collider_outside_of_screen(&b->collider) != DIR_NONE) {
    b->alive = false;
  }
}

void
bullet_render(Entities *e) {
  Bullet *b = &e->bullet;
  if (b->alive) rect(b->collider.position, b->collider.w, b->collider.h, 2);
}
