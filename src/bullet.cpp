#include "include/bullet.h"
#include "include/core.h"
#include "include/renderer.h"

void
bullet_start(Entities *e) {
  Bullet *b = &e->bullet;
  for (u32 i = 0; i < BULLET_CAP; i++)
    b->collider[i].size = { TILE_SIZE / 4, TILE_SIZE / 4 };
}

void
bullet_update(Entities *e, f32 dt) {
  Bullet *b = &e->bullet;
  /* remove dead bullets */
  for (i32 i = b->amount - 1; i >= 0; i--) {
    if (b->alive[i]) continue;
    for (i32 j = i; j < b->amount - 1; j++) {
      b->alive[j] = true;
      b->mover[j] = b->mover[j + 1];
      b->collider[j] = b->collider[j + 1];
    }
    b->amount--;
  }
  /* move bullets */
  for (u32 i = 0; i < b->amount; i++) {
    UpdateMoverResult mover_result = update_mover(&b->mover[i], &b->collider[i], dt, false, false);
    if (mover_result.collided_x || mover_result.collided_y || collider_outside_of_screen(&b->collider[i]) != DIR_NONE) b->alive[i] = false;
  }
}

void
bullet_render(Entities *e) {
  Bullet *b = &e->bullet;
  for (u32 i = 0; i < b->amount; i++) {
    rect(b->collider[i].position, b->collider[i].w, b->collider[i].h, 2);
  }
}
