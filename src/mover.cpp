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
    collider->position.x += i32(mover->remainder.x);
    mover->remainder.x -= i32(mover->remainder.x);
  }
  if (ABS(mover->remainder.y) >= 1) {
    collider->position.y += i32(mover->remainder.y);
    mover->remainder.y -= i32(mover->remainder.y);
  }
  if (collider->position.x != old_position.x) {
    i32 tiley0 = old_position.y >> TILE_SHIFT;
    i32 tiley1 = (old_position.y + TILE_SIZE - 1) >> TILE_SHIFT;
    i32 tilex0 = collider->position.x >> TILE_SHIFT;
    i32 tilex1 = (collider->position.x + TILE_SIZE - 1) >> TILE_SHIFT;
    if (get_map_tile(tilex0, tiley0) == TILE_SOLID ||
        get_map_tile(tilex0, tiley1) == TILE_SOLID ||
        get_map_tile(tilex1, tiley0) == TILE_SOLID ||
        get_map_tile(tilex1, tiley1) == TILE_SOLID) {
      if (resolve_collision) {
        if (mover->velocity.x > 0) {
          collider->position.x = tilex0 * TILE_SIZE;
        } else {
          collider->position.x = (tilex0 + 1) * TILE_SIZE;
        }
        mover->velocity.x = 0;
      }
      result.collided_x = true;
    }
  }
  if (collider->position.y != old_position.y) {
    i32 tiley0 = collider->position.y >> TILE_SHIFT;
    i32 tiley1 = (collider->position.y + TILE_SIZE - 1) >> TILE_SHIFT;
    i32 tilex0 = old_position.x >> TILE_SHIFT;
    i32 tilex1 = (old_position.x + TILE_SIZE - 1) >> TILE_SHIFT;
    if (get_map_tile(tilex0, tiley0) == TILE_SOLID ||
        get_map_tile(tilex0, tiley1) == TILE_SOLID ||
        get_map_tile(tilex1, tiley0) == TILE_SOLID ||
        get_map_tile(tilex1, tiley1) == TILE_SOLID) {
      if (resolve_collision) {
        if (mover->velocity.y > 0) {
          collider->position.y = tiley0 * TILE_SIZE;
        } else {
          collider->position.y = (tiley0 + 1) * TILE_SIZE;
        }
        mover->velocity.y = 0;
      }
      result.collided_y = true;
    }
  }
  return result;
}

bool
is_on_ground(V2i position) {
  i32 y  = (position.y + TILE_SIZE) >> TILE_SHIFT;
  i32 x0 = position.x >> TILE_SHIFT;
  i32 x1 = (position.x + TILE_SIZE - 1) >> TILE_SHIFT;
  return get_map_tile(x0, y) == TILE_SOLID || get_map_tile(x1, y) == TILE_SOLID;
}
