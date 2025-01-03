#include "include/mover.h"
#include "include/math.h"
#include "include/map.h"
#include "include/core.h"
#include "include/renderer.h"

void
update_mover(Mover *mover, f32 dt) {
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
    i32 celly0 = old_position.y >> TILE_SHIFT;
    i32 celly1 = (old_position.y + TILE_SIZE - 1) >> TILE_SHIFT;
    i32 cellx0 = mover->collider.position.x >> TILE_SHIFT;
    i32 cellx1 = (mover->collider.position.x + TILE_SIZE - 1) >> TILE_SHIFT;
    if (get_map_cell(cellx0, celly0) == CELL_SOLID ||
        get_map_cell(cellx0, celly1) == CELL_SOLID ||
        get_map_cell(cellx1, celly0) == CELL_SOLID ||
        get_map_cell(cellx1, celly1) == CELL_SOLID) {
      if (mover->velocity.x > 0) {
        mover->collider.position.x = cellx0 * TILE_SIZE;
      } else {
        mover->collider.position.x = (cellx0 + 1) * TILE_SIZE;
      }
      mover->velocity.x = 0;
    }
  }
  if (mover->collider.position.y != old_position.y) {
    i32 celly0 = mover->collider.position.y >> TILE_SHIFT;
    i32 celly1 = (mover->collider.position.y + TILE_SIZE - 1) >> TILE_SHIFT;
    i32 cellx0 = old_position.x >> TILE_SHIFT;
    i32 cellx1 = (old_position.x + TILE_SIZE - 1) >> TILE_SHIFT;
    if (get_map_cell(cellx0, celly0) == CELL_SOLID ||
        get_map_cell(cellx1, celly0) == CELL_SOLID ||
        get_map_cell(cellx0, celly1) == CELL_SOLID ||
        get_map_cell(cellx1, celly1) == CELL_SOLID) {
      if (mover->velocity.y > 0) {
        mover->collider.position.y = celly0 * TILE_SIZE;
      } else {
        mover->collider.position.y = (celly0 + 1) * TILE_SIZE;
      }
      mover->velocity.y = 0;
    }
  }
}
