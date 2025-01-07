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
  u8 bullet_max;
  bool flip;
  bool alive;
};

#define BULLET_CAP 6
struct Bullet {
  Collider collider[BULLET_CAP];
  Mover mover[BULLET_CAP];
  bool alive[BULLET_CAP];
  u8 amount;
};

struct Entities {
  Player player;
  Bullet bullet;
};

#endif/*_ENTITIES_H_*/
