#include "include/map.h"
#include "include/core.h"
#include "include/player.h"
#include "include/renderer.h"
#include "include/debug.h"
#include "include/res/map.h"

static u8 g_map_index;
static u8 g_map_next_index;
static SurroundingMap g_map_direction_from_prv;
static bool g_is_changing_map;
static f32 g_wait;

#define MAP_NONE ((SurroundingMap)-1)

static u8
get_map_tile_unsafe(int x, int y) {
  return (g_map_tiles[g_map_index][y * (MAP_WIDTH >> 1) + (x >> 1)] >> (4 * (x & 1))) & 0xf;
}

static void
load_map_internal(Entities *e, u8 map_index) {
  g_map_index = map_index;
  bool found_player = false;
  V2i player_pos = {};
  for (i32 y = 0; y < MAP_HEIGHT; y++) {
    for (i32 x = 0; x < MAP_WIDTH; x++) {
      V2i tile_pos = {x * TILE_SIZE, y * TILE_SIZE};
      switch (get_map_tile_unsafe(x, y)) {
      case TILE_PLAYER:
        if (!found_player) {
          found_player = true;
          player_pos = tile_pos;
        } else if (g_map_direction_from_prv != MAP_NONE) {
          switch (g_map_direction_from_prv) {
          case MAP_TOP:    if (tile_pos.y < player_pos.y) player_pos = tile_pos; break;
          case MAP_LEFT:   if (tile_pos.x < player_pos.x) player_pos = tile_pos; break;
          case MAP_BOTTOM: if (tile_pos.y > player_pos.y) player_pos = tile_pos; break;
          case MAP_RIGHT:  if (tile_pos.x > player_pos.x) player_pos = tile_pos; break;
          }
        }
        break;
      default:
        break;
      }
    }
  }
  player_start(e, player_pos);
}

void
map_system_start(Entities *e) {
  g_map_direction_from_prv = MAP_NONE;
  load_map_internal(e, 0);
  g_map_next_index = g_map_index;
  g_wait = 0;
}

void
load_map(u8 map_index) {
  if (map_index >= MAP_AMOUNT) return;
  g_map_next_index = map_index;
  g_is_changing_map = true;
  g_wait = 0.2f;
  fade_out();
}

MapTile
get_map_tile(int x, int y) {
  if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return TILE_NONE;
  return get_map_tile_unsafe(x, y);
}

i8
get_next_map(SurroundingMap direction) {
  switch (direction) {
    case MAP_TOP:    g_map_direction_from_prv = MAP_BOTTOM; break;
    case MAP_LEFT:   g_map_direction_from_prv = MAP_RIGHT;  break;
    case MAP_BOTTOM: g_map_direction_from_prv = MAP_TOP;    break;
    case MAP_RIGHT:  g_map_direction_from_prv = MAP_LEFT;   break;
  }
  return g_map_surrounding[g_map_index][direction];
}

bool
is_changing_map(void) {
  return g_is_changing_map;
}

void
map_system_update(Entities *e, f32 dt) {
  if (!g_is_changing_map) return;
  if (!in_fade()) {
    if (g_wait > 0) {
      g_wait -= dt;
    } else if (g_map_next_index != g_map_index) {
      load_map_internal(e, g_map_next_index);
      fade_in();
    } else {
      g_is_changing_map = false;
    }
  }
}

void
debug_render_map(void) {
  if (g_map_index < MAP_AMOUNT)
  for (i32 y = 0; y < MAP_HEIGHT; y++) {
    for (i32 x = 0; x < MAP_WIDTH; x++) {
      if (get_map_tile_unsafe(x, y) == TILE_SOLID) {
        rect_outline(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2);
      }
    }
  }
}
