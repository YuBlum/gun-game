#include "include/map.h"
#include "include/core.h"
#include "include/player.h"
#include "include/renderer.h"
#include "include/res/map.h"

static u8 g_map_index;

static u8
get_map_pixel(int x, int y) {
  return (map_color[g_map_index][y * (MAP_WIDTH >> 1) + (x >> 1)] >> (4 * (x & 1))) & 0xf;
}

void
load_map(Entities *e, u8 map_index) {
  if (map_index >= MAP_FRAMES) return;
  g_map_index = map_index;
  for (i32 y = 0; y < MAP_HEIGHT; y++) {
    for (i32 x = 0; x < MAP_WIDTH; x++) {
      switch (get_map_pixel(x, y)) {
      case CELL_PLAYER:
        player_start(e, {x * TILE_SIZE, y * TILE_SIZE});
        break;
      default:
        break;
      }
    }
  }
}

MapCell
get_map_cell(int x, int y) {
  if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return CELL_NONE;
  return get_map_pixel(x, y);
}

void
debug_render_map(void) {
  for (i32 y = 0; y < MAP_HEIGHT; y++) {
    for (i32 x = 0; x < MAP_WIDTH; x++) {
      if (get_map_pixel(x, y) == CELL_SOLID) {
        rect_outline(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2);
      }
    }
  }
}
