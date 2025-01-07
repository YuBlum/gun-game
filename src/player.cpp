#include "include/player.h"
#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/map.h"
#include "include/debug.h"
#include "include/res/spr-test.h"

#define MAX_SPEED                  60.0f
#define GROUND_ACCELERATION        650.0f
#define AIR_ACCELERATION           800.0f
#define FRICTION                   650.0f
#define START_WITH_JUMP_VELOCITY  -125.0f
#define JUMP_VELOCITY             -75.0f
#define JUMPING_WEIGHT             1.50f
#define FALLING_WEIGHT             1.00f
#define VARIABLE_JUMP_TIMER_MAX    0.15f
#define JUMP_BUFFER_TIMER_MAX      0.12f
#define COYOTE_TIMER_MAX           0.06f
#define SHOOT_IMPULSE_VELOCITY     125.0f
#define RELOAD_TIMER_MAX           1.00f
#define BULLET_SPEED               200.0f

void
player_start(Entities *e) {
  Player *p = &e->player;
  *p = {};
  p->collider.size = { TILE_SIZE, TILE_SIZE };
  p->bullet_max = 1;
}

void
player_setup(Entities *e, V2i position, bool start_with_jump) {
  Player *p = &e->player;
  p->alive               = true;
  p->variable_jump_timer = 0.0f;
  p->jump_buffer_timer   = 0.0f;
  p->coyote_timer        = 0.0f;
  p->mover               = {};
  p->animator            = {};
  p->collider.position   = position;
  if (start_with_jump) p->mover.velocity.y = START_WITH_JUMP_VELOCITY;
}

void
player_update(Entities *e, f32 dt) {
  Player *p = &e->player;
  bool on_ground = is_on_ground(&p->collider);
  /* change map if necessary */
  load_map(
    get_next_map(
      collider_outside_of_screen(&p->collider)
    )
  );
  /* horizontal movement */
  f32 input = f32(is_key_down(KEY_RIGHT) - is_key_down(KEY_LEFT));
  if (input < 0) p->flip = true;
  else if (input > 0) p->flip = false;
  f32 acceleration = on_ground ? GROUND_ACCELERATION : AIR_ACCELERATION;
  p->mover.velocity.x += input * acceleration * dt;
  if (ABS(p->mover.velocity.x) > MAX_SPEED) {
    p->mover.velocity.x = approach(
      p->mover.velocity.x,
      MAX_SPEED * input,
      2000 * dt
    );
  }
  if (input == 0.0f) p->mover.velocity.x = approach(p->mover.velocity.x, 0, FRICTION * dt);
  /* jump */
  if (is_key_click(KEY_A)) p->jump_buffer_timer = JUMP_BUFFER_TIMER_MAX;
  if (p->jump_buffer_timer > 0) p->jump_buffer_timer -= dt;
  if (on_ground) p->coyote_timer = COYOTE_TIMER_MAX;
  if (p->coyote_timer > 0) p->coyote_timer -= dt;
  if (p->jump_buffer_timer > 0 && p->coyote_timer > 0) {
    p->variable_jump_timer = VARIABLE_JUMP_TIMER_MAX;
    p->jump_buffer_timer = 0;
    p->coyote_timer = 0;
  }
  if (p->variable_jump_timer > 0) {
    if (!is_key_down(KEY_A)) p->variable_jump_timer = 0;
    p->mover.velocity.y = JUMP_VELOCITY;
    p->variable_jump_timer -= dt;
  }
  p->mover.weight = p->mover.velocity.y < 0 ? JUMPING_WEIGHT : FALLING_WEIGHT;
  /* shoot */
  if (p->reload_timer > 0.0f) p->reload_timer -= dt;
  if (is_key_down(KEY_B) && e->bullet.amount < p->bullet_max && p->reload_timer <= 0.0f) {
    e->bullet.alive[e->bullet.amount] = true;
    e->bullet.mover[e->bullet.amount].remainder = {};
    e->bullet.collider[e->bullet.amount].position = p->collider.position + p->collider.size / 2;
    int input_y = is_key_down(KEY_DOWN) - is_key_down(KEY_UP);
    Direction aim_direction = input_y < 0 ? DIR_TOP : input_y > 0 ? DIR_BOTTOM : p->flip ? DIR_LEFT : DIR_RIGHT;
    switch (aim_direction) {
    case DIR_TOP: 
      e->bullet.mover[e->bullet.amount].velocity = { +0.0, -BULLET_SPEED };
      break;
    case DIR_LEFT:
      e->bullet.mover[e->bullet.amount].velocity = { -BULLET_SPEED, +0.0 };
      break;
    case DIR_BOTTOM:
      e->bullet.mover[e->bullet.amount].velocity = { +0.0, +BULLET_SPEED };
      p->mover.velocity.y -= SHOOT_IMPULSE_VELOCITY;
      break;
    case DIR_RIGHT:
      e->bullet.mover[e->bullet.amount].velocity = { +BULLET_SPEED, +0.0 };
      break;
    }
    e->bullet.amount++;
    if (e->bullet.amount >= p->bullet_max) p->reload_timer = RELOAD_TIMER_MAX;
  }
  /* update components */
  update_animator(&p->animator, SPR_TEST_FRAMES, g_spr_test_frame_duration, dt);
  update_mover(&p->mover, &p->collider, dt);
}

void
player_render(Entities *e) {
  Player *p = &e->player;
  draw_animator(p->animator, p->collider.position, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)g_spr_test_pixels, 3, p->flip);
}
