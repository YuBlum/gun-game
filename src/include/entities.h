#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include "include/math.h"
#include "include/animator.h"
#include "include/collider.h"
#include "include/mover.h"

struct Player {
  Collider collider;
  Mover mover;
  Animator animator;
  f32 variable_jump_timer;
  f32 jump_buffer_timer;
  f32 coyote_timer;
  f32 reload_timer;
  u8 loop_index;
  bool flip;
  bool alive;
  Direction aim_direction;
};

struct Bullet {
  Collider collider;
  Mover mover;
  bool alive;
};

struct Entities {
  Player player;
  Bullet bullet;
};

#endif/*_ENTITIES_H_*/
