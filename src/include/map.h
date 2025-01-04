#ifndef _MAP_H_
#define _MAP_H_

#include "include/game.h"

#define TILE_NONE   0x0
#define TILE_SOLID  0x3
#define TILE_PLAYER 0xe

typedef u8 MapTile;

enum SurroundingMap : u8 {
  MAP_TOP = 0,
  MAP_LEFT,
  MAP_BOTTOM,
  MAP_RIGHT,
};

void map_system_start(Entities *e);
void load_map(u8 map_index);
MapTile get_map_tile(int x, int y);
i8 get_next_map(SurroundingMap direction);
bool is_changing_map(void);
void map_system_update(Entities *e, f32 dt);
void debug_render_map(void);

#endif/*_MAP_H_*/
