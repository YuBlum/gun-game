#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include "include/math.h"
#include "include/animator.h"
#include "include/collider.h"
#include "include/mover.h"

#define ENTITY_CAP 0x100

struct Player {
  Collider collider;
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

#endif/*_ENTITIES_H_*/
