#include "include/collider.h"

bool
aabb_collision(V2i p0, Collider *c0, V2i p1, Collider *c1) {
  return p0.x + c0->size.x > p1.x &&
         p0.x < p1.x + c1->size.x &&
         p0.y + c0->size.y > p1.y &&
         p0.y < p1.y + c1->size.y;
}
