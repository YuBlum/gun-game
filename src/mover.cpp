#include "include/mover.h"
#include "include/math.h"
#include "include/map.h"
#include "include/core.h"
#include "include/renderer.h"

void
update_mover(Mover *mover, f32 dt) {
  if (mover->has_gravity) {
    mover->velocity.y += GRAVITY * mover->weight * dt;
    if (mover->velocity.y > +GRAVITY_CAP) mover->velocity.y = +GRAVITY_CAP;
    if (mover->velocity.y < -GRAVITY_CAP) mover->velocity.y = -GRAVITY_CAP;
  }
  mover->remainder += mover->velocity * dt;
  V2i old_position = mover->collider.position;
  if (ABS(mover->remainder.x) >= 1) {
    mover->collider.position.x += i32(mover->remainder.x);
    mover->remainder.x -= i32(mover->remainder.x);
  }
  if (ABS(mover->remainder.y) >= 1) {
    mover->collider.position.y += i32(mover->remainder.y);
    mover->remainder.y -= i32(mover->remainder.y);
  }
  if (mover->collider.position.x != old_position.x) {
    i32 tiley0 = old_position.y >> TILE_SHIFT;
    i32 tiley1 = (old_position.y + TILE_SIZE - 1) >> TILE_SHIFT;
    i32 tilex0 = mover->collider.position.x >> TILE_SHIFT;
    i32 tilex1 = (mover->collider.position.x + TILE_SIZE - 1) >> TILE_SHIFT;
    if (get_map_tile(tilex0, tiley0) == TILE_SOLID ||
        get_map_tile(tilex0, tiley1) == TILE_SOLID ||
        get_map_tile(tilex1, tiley0) == TILE_SOLID ||
        get_map_tile(tilex1, tiley1) == TILE_SOLID) {
      if (mover->velocity.x > 0) {
        mover->collider.position.x = tilex0 * TILE_SIZE;
      } else {
        mover->collider.position.x = (tilex0 + 1) * TILE_SIZE;
      }
      mover->velocity.x = 0;
    }
  }
  if (mover->collider.position.y != old_position.y) {
    i32 tiley0 = mover->collider.position.y >> TILE_SHIFT;
    i32 tiley1 = (mover->collider.position.y + TILE_SIZE - 1) >> TILE_SHIFT;
    i32 tilex0 = old_position.x >> TILE_SHIFT;
    i32 tilex1 = (old_position.x + TILE_SIZE - 1) >> TILE_SHIFT;
    mover->on_ground = get_map_tile(tilex0, tiley1) == TILE_SOLID || get_map_tile(tilex1, tiley1) == TILE_SOLID;
    if (get_map_tile(tilex0, tiley0) == TILE_SOLID ||
        get_map_tile(tilex1, tiley0) == TILE_SOLID ||
        mover->on_ground) {
      if (mover->velocity.y > 0) {
        mover->collider.position.y = tiley0 * TILE_SIZE;
      } else {
        mover->collider.position.y = (tiley0 + 1) * TILE_SIZE;
      }
      mover->velocity.y = 0;
    }
  }
}
