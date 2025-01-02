#ifndef _MAP_H_
#define _MAP_H_

#include "include/game.h"

#define CELL_NONE   0x0
#define CELL_SOLID  0x3
#define CELL_PLAYER 0xe

typedef u8 MapCell;

void load_map(Entities *e, u8 map_index);
MapCell get_map_cell(int x, int y);
void debug_render_map(void);

#endif/*_MAP_H_*/
