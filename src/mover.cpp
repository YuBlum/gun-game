#include "include/mover.h"
#include "include/math.h"
#include "include/map.h"
#include "include/core.h"
#include "include/renderer.h"

UpdateMoverResult
update_mover(Mover *mover, Collider *collider, f32 dt, bool use_gravity, bool resolve_collision) {
  UpdateMoverResult result = {};
  if (use_gravity) {
    mover->velocity.y += GRAVITY * mover->weight * dt;
    if (mover->velocity.y > +GRAVITY_CAP) mover->velocity.y = +GRAVITY_CAP;
    if (mover->velocity.y < -GRAVITY_CAP) mover->velocity.y = -GRAVITY_CAP;
  }
  mover->remainder += mover->velocity * dt;
  V2i old_position = collider->position;
  if (ABS(mover->remainder.x) >= 1) {
    collider->x += i32(mover->remainder.x);
    mover->remainder.x -= i32(mover->remainder.x);
  }
  if (ABS(mover->remainder.y) >= 1) {
    collider->y += i32(mover->remainder.y);
    mover->remainder.y -= i32(mover->remainder.y);
  }
  if (collider->x != old_position.x) {
    i32 tiley0 = old_position.y >> TILE_SHIFT;
    i32 tiley1 = (old_position.y + collider->h - 1) >> TILE_SHIFT;
    i32 tilex0 = collider->x >> TILE_SHIFT;
    i32 tilex1 = (collider->x + collider->w - 1) >> TILE_SHIFT;
    if (get_map_tile(tilex0, tiley0) == TILE_SOLID ||
        get_map_tile(tilex0, tiley1) == TILE_SOLID ||
        get_map_tile(tilex1, tiley0) == TILE_SOLID ||
        get_map_tile(tilex1, tiley1) == TILE_SOLID) {
      if (resolve_collision) {
        if (mover->velocity.x > 0) {
          collider->x = (tilex1 << TILE_SHIFT) - collider->w;
        } else {
          collider->x = (tilex0 + 1) << TILE_SHIFT;
        }
        mover->velocity.x = 0;
      }
      result.collided_x = true;
    }
  }
  if (collider->y != old_position.y) {
    i32 tiley0 = collider->y >> TILE_SHIFT;
    i32 tiley1 = (collider->y + collider->h - 1) >> TILE_SHIFT;
    i32 tilex0 = old_position.x >> TILE_SHIFT;
    i32 tilex1 = (old_position.x + collider->w - 1) >> TILE_SHIFT;
    if (get_map_tile(tilex0, tiley0) == TILE_SOLID ||
        get_map_tile(tilex0, tiley1) == TILE_SOLID ||
        get_map_tile(tilex1, tiley0) == TILE_SOLID ||
        get_map_tile(tilex1, tiley1) == TILE_SOLID) {
      if (resolve_collision) {
        if (mover->velocity.y > 0) {
          collider->y = (tiley1 << TILE_SHIFT) - collider->h;
        } else {
          collider->y = (tiley0 + 1) << TILE_SHIFT;
        }
        mover->velocity.y = 0;
      }
      result.collided_y = true;
    }
  }
  return result;
}
