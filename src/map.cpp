#include "include/map.h"
#include "include/core.h"
#include "include/player.h"
#include "include/renderer.h"
#include "include/debug.h"
#include "include/res/map.h"

static u8 g_map_index;
static u8 g_map_next_index;
static SurroundingMap g_map_direction_from_prv;
static bool g_change_map;
static bool g_in_map_transition;
static bool g_reloading;

#define MAP_NONE ((SurroundingMap)-1)

static u8
get_map_tile_unsafe(int x, int y) {
  return (g_map_tiles[g_map_index][y * (MAP_WIDTH >> 1) + (x >> 1)] >> (4 * (x & 1))) & 0xf;
}

static void
load_map_internal(Entities *e, u8 map_index) {
  g_map_index = map_index;
  bool found_player = false;
  bool start_with_jump = false;
  V2i player_pos = e->player.mover.collider.position;
  if (e->player.alive && g_map_direction_from_prv != MAP_NONE) {
    switch (g_map_direction_from_prv) {
    case MAP_TOP:    player_pos.y = 0;                                    break;
    case MAP_LEFT:   player_pos.x = 0;                                    break;
    case MAP_RIGHT:  player_pos.x = CANVAS_H - 8;                         break;
    case MAP_BOTTOM: player_pos.y = CANVAS_W - 8; start_with_jump = true; break;
    }
  }
  for (i32 y = 0; y < MAP_HEIGHT; y++) {
    for (i32 x = 0; x < MAP_WIDTH; x++) {
      V2i tile_pos = {x * TILE_SIZE, y * TILE_SIZE};
      switch (get_map_tile_unsafe(x, y)) {
      case TILE_PLAYER:
      {
        if (e->player.alive) break;
        bool change_player = false;
        if (g_map_direction_from_prv != MAP_NONE) {
          switch (g_map_direction_from_prv) {
          case MAP_TOP:    if (tile_pos.y < player_pos.y) { change_player = true; } break;
          case MAP_LEFT:   if (tile_pos.x < player_pos.x) { change_player = true; } break;
          case MAP_BOTTOM: if (tile_pos.y > player_pos.y) { change_player = true; } break;
          case MAP_RIGHT:  if (tile_pos.x > player_pos.x) { change_player = true; } break;
          }
        }
        if (!found_player || change_player) {
          found_player = true;
          player_pos = tile_pos;
        }
      } break;
      default:
        break;
      }
    }
  }
  player_start(e, player_pos, start_with_jump);
}

void
map_system_start(Entities *e) {
  g_map_direction_from_prv = MAP_NONE;
  load_map_internal(e, 0);
  g_map_next_index = g_map_index;
  g_change_map = false;
  g_in_map_transition = false;
  g_reloading = false;
}

void
load_map(u8 map_index) {
  if (map_index >= MAP_AMOUNT) return;
  g_map_next_index = map_index;
  g_in_map_transition = true;
  g_change_map = true;
  fade_out();
}

void
reload_map(void) {
  g_reloading = true;
  load_map(g_map_index);
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
in_map_transition(void) {
  return g_in_map_transition;
}

void
map_system_update(Entities *e) {
  if (!g_in_map_transition) return;
  if (!in_fade()) {
    if (g_change_map) {
      if (g_reloading) {
        g_reloading = false;
        e->player.alive = false;
      }
      g_change_map = false;
      load_map_internal(e, g_map_next_index);
      fade_in();
    } else {
      g_in_map_transition = false;
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
