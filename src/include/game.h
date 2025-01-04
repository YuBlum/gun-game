#ifndef _GAME_H_
#define _GAME_H_

#include "include/types.h"
#include "include/math.h"
#include "include/animator.h"
#include "include/mover.h"

#define ENTITY_CAP 0x100

struct Player {
  Mover mover;
  Animator animator;
  f32 variable_jump_timer;
  f32 jump_buffer_timer;
  f32 coyote_timer;
  bool alive;
};

struct Entities {
  Player player;
};

void game_start(void);
void game_update(f32);
void game_render(void);

#endif/*_GAME_H_*/
