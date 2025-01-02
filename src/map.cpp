#include "include/map.h"
#include "include/core.h"
#include "include/player.h"
#include "include/renderer.h"
#include "include/res/map-test.h"

struct Map {
  u8 *cells;
  u16 width;
  u16 height;
};

static u8 g_map_index;
static Map g_maps[] = {
  { (u8 *)map_test_color, MAP_TEST_WIDTH, MAP_TEST_HEIGHT },
};
#define MAPS_AMOUNT (sizeof (g_maps) / sizeof (g_maps[0]))

void
load_map(Entities *e, u8 map_index) {
  if (map_index >= MAPS_AMOUNT) return;
  g_map_index = map_index;
  for (i32 y = 0; y < g_maps[map_index].height; y++) {
    for (i32 x = 0; x < g_maps[map_index].width; x++) {
      switch (get_buffer_pixel(x, y, g_maps[map_index].width >> 1, g_maps[map_index].cells)) {
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
  if (x < 0 || x >= g_maps[g_map_index].width || y < 0 || y >= g_maps[g_map_index].height) return CELL_NONE;
  return get_buffer_pixel(x, y, g_maps[g_map_index].width >> 1, g_maps[g_map_index].cells);
}

void
debug_render_map(void) {
  for (i32 y = 0; y < g_maps[g_map_index].height; y++) {
    for (i32 x = 0; x < g_maps[g_map_index].width; x++) {
      if (get_buffer_pixel(x, y, g_maps[g_map_index].width >> 1, g_maps[g_map_index].cells) == CELL_SOLID) {
        rect_outline(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, CELL_SOLID);
      }
    }
  }
}
