#include "include/collider.h"
#include "include/core.h"
#include "include/map.h"
#include "include/debug.h"
#ifdef DEBUG
#  include "include/window.h"
#endif

bool
collider_on_collider(Collider *c0, Collider *c1) {
  return c0->position.x + c0->size.x > c1->position.x              &&
         c0->position.x              < c1->position.x + c1->size.x &&
         c0->position.y + c0->size.y > c1->position.y              &&
         c0->position.y              < c1->position.y + c1->size.y;
}

bool
is_on_ground(Collider *collider) {
  i32 y  = (collider->position.y + collider->size.y) >> TILE_SHIFT;
  i32 x0 = collider->position.x >> TILE_SHIFT;
  i32 x1 = (collider->position.x + collider->size.x - 1) >> TILE_SHIFT;
  return get_map_tile(x0, y) == TILE_SOLID || get_map_tile(x1, y) == TILE_SOLID;
}

Direction
collider_outside_of_screen(Collider *c) {
  if (c->x + c->w > CANVAS_W ) return DIR_RIGHT;
  if (c->x        < 0        ) return DIR_LEFT;
  if (c->y + c->h > CANVAS_H ) return DIR_BOTTOM;
  if (c->y        < TILE_SIZE) return DIR_TOP;
  return DIR_NONE;
}

#ifdef DEBUG
void
debug_render_collider(Collider *c) {
  rect_debug(c->position, c->w, c->h);
}
#endif
