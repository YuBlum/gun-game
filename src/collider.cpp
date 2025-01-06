#include "include/collider.h"
#include "include/core.h"
#include "include/debug.h"
#ifdef DEBUG
#  include "include/window.h"
#endif

bool
aabb_collision(Collider *c0, Collider *c1) {
  return c0->position.x + c0->size.x > c1->position.x              &&
         c0->position.x              < c1->position.x + c1->size.x &&
         c0->position.y + c0->size.y > c1->position.y              &&
         c0->position.y              < c1->position.y + c1->size.y;
}

#ifdef DEBUG
void
debug_render_collider(Collider *c) {
  rect_debug(c->position, u16(c->size.x), u16(c->size.y));
}
#endif
