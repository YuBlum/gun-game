#include "include/map.h"
#include "include/core.h"
#include "include/player.h"
#include "include/debug.h"
#include "include/math.h"
#include "include/res/spr_wall.h"
#include "include/res/map.h"
#include "include/renderer.h"
#ifdef DEBUG
#  include "include/window.h"
#endif

static u8 g_map_index;
static u8 g_map_next_index;
static Direction g_map_direction_from_prv;
static bool g_change_map;
static bool g_in_map_transition;
static bool g_reloading;

static u8 tile_sprite[(MAP_W >> 1) * MAP_H];

static u8
get_map_buffer_unsafe(int x, int y, u8 *buffer) {
  return (buffer[y * (MAP_W >> 1) + (x >> 1)] >> (4 * (x & 1))) & 0xf;
}

static void
set_map_buffer_unsafe(int x, int y, u8 *buffer, u8 val) {
  u8 shift = 4 * (x & 1);
  x >>= 1;
  buffer[y * (MAP_W >> 1) + x] = (val << shift) | ((0xf0 >> shift) & buffer[y * (MAP_W >> 1) + x]);
}

static void
load_map_internal(Entities *e, u8 map_index) {
  g_map_index = map_index;
  e->bullet.alive = false;
  bool found_player = false;
  bool player_start_with_jump = false;
  V2i player_pos = e->player.collider.position;
  if (e->player.alive && g_map_direction_from_prv != DIR_NONE) {
    switch (g_map_direction_from_prv) {
    case DIR_TOP:    player_pos.y = TILE_SIZE;                                                      break;
    case DIR_LEFT:   player_pos.x = 0;                                                              break;
    case DIR_RIGHT:  player_pos.x = CANVAS_H - e->player.collider.h;                                break;
    case DIR_BOTTOM: player_pos.y = CANVAS_W - e->player.collider.w; player_start_with_jump = true; break;
    }
  }
  for (i32 y = 0; y < MAP_H; y++) {
    for (i32 x = 0; x < MAP_W; x++) {
      V2i tile_pos = {x << TILE_SHIFT, (y + 1) << TILE_SHIFT};
      switch (get_map_buffer_unsafe(x, y, g_map_tiles[g_map_index])) {
      case TILE_PLAYER:
      {
        if (e->player.alive) break;
        bool change_player = false;
        if (g_map_direction_from_prv != DIR_NONE) {
          switch (g_map_direction_from_prv) {
          case DIR_TOP:    if (tile_pos.y < player_pos.y) { change_player = true; } break;
          case DIR_LEFT:   if (tile_pos.x < player_pos.x) { change_player = true; } break;
          case DIR_BOTTOM: if (tile_pos.y > player_pos.y) { change_player = true; } break;
          case DIR_RIGHT:  if (tile_pos.x > player_pos.x) { change_player = true; } break;
          }
        }
        if (!found_player || change_player) {
          found_player = true;
          player_pos = tile_pos;
        }
      } break;
      case TILE_SOLID:
      {
        auto percent = rand32() % 100;
        u8 val = 0;
        if (percent < 10) {
          val = rand32() % 2 + 4;
        } else if (percent < 40) {
          val = rand32() % 3 + 1;
        }
        set_map_buffer_unsafe(x, y, tile_sprite, val);
      } break;
      default:
        break;
      }
    }
  }
  player_setup(e, player_pos, player_start_with_jump);
}

void
map_system_start(Entities *e) {
  g_map_direction_from_prv = DIR_NONE;
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
  y--;
  if (x < 0 || x >= MAP_W || y < 0 || y >= MAP_H) return TILE_NONE;
  return get_map_buffer_unsafe(x, y, g_map_tiles[g_map_index]);
}

i8
get_next_map(Direction direction) {
  switch (direction) {
    case DIR_TOP:    g_map_direction_from_prv = DIR_BOTTOM; break;
    case DIR_LEFT:   g_map_direction_from_prv = DIR_RIGHT;  break;
    case DIR_BOTTOM: g_map_direction_from_prv = DIR_TOP;    break;
    case DIR_RIGHT:  g_map_direction_from_prv = DIR_LEFT;   break;
    case DIR_NONE:   return -1;
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
render_map(void) {
  for (i32 y = 0; y < MAP_H; y++) {
    for (i32 x = 0; x < MAP_W; x++) {
      if (get_map_buffer_unsafe(x, y, g_map_tiles[g_map_index]) == TILE_SOLID) {
        color_buffer(x << TILE_SHIFT, (y + 1) << TILE_SHIFT, SPR_WALL_W, SPR_WALL_H, g_spr_wall_pixels[get_map_buffer_unsafe(x, y, tile_sprite)], 2, false);
      }
    }
  }
}

#ifdef DEBUG
void
debug_render_map(void) {
  for (i32 y = 0; y < MAP_H; y++) {
    for (i32 x = 0; x < MAP_W; x++) {
      if (get_map_buffer_unsafe(x, y, g_map_tiles[g_map_index]) == TILE_SOLID) {
        rect_debug(x << TILE_SHIFT, (y + 1) << TILE_SHIFT, TILE_SIZE, TILE_SIZE);
      }
    }
  }
}
#endif
