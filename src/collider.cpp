#include "include/collider.h"
#include "include/core.h"

bool
aabb_collision(Collider *c0, Collider *c1) {
  return c0->position.x + TILE_SIZE > c1->position.x             &&
         c0->position.x             < c1->position.x + TILE_SIZE &&
         c0->position.y + TILE_SIZE > c1->position.y             &&
         c0->position.y             < c1->position.y + TILE_SIZE;
}
