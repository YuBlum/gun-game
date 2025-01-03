#ifndef _GAME_H_
#define _GAME_H_

#include "include/types.h"
#include "include/math.h"
#include "include/sprite.h"
#include "include/mover.h"

#define ENTITY_CAP 0x100

struct Player {
  Mover mover;
  Sprite sprite;
  f32 jump_timer;
};

struct Entities {
  Player player;
};

void game_start(void);
void game_update(f32);
void game_render(void);

#endif/*_GAME_H_*/
