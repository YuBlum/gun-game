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

void
player_start(Entities *e, V2i position, bool start_with_jump) {
  Player *p = &e->player;
  p->alive = true;
  p->mover = {};
  p->animator = {};
  p->coyote_timer = 0;
  p->jump_buffer_timer = 0;
  p->variable_jump_timer = 0;
  p->mover.weight            = 1.0f;
  p->mover.has_gravity       = true;
  p->mover.collider.tag      = COL_PLAYER;
  p->mover.collider.position = position;
  if (start_with_jump) p->mover.velocity.y = START_WITH_JUMP_VELOCITY;
}

void
player_update(Entities *e, f32 dt) {
  Player *p = &e->player;
  /* change map */
  {
    i8 next_map = -1;
    if (p->mover.collider.position.x + SPR_TEST_WIDTH  > CANVAS_W) next_map = get_next_map(MAP_RIGHT);
    if (p->mover.collider.position.x                   < 0       ) next_map = get_next_map(MAP_LEFT);
    if (p->mover.collider.position.y + SPR_TEST_HEIGHT > CANVAS_H) next_map = get_next_map(MAP_BOTTOM);
    if (p->mover.collider.position.y                   < 0       ) next_map = get_next_map(MAP_TOP);
    if (next_map != -1) load_map(next_map);
  }
  /* horizontal movement */
  f32 input = f32(is_key_down(KEY_RIGHT) - is_key_down(KEY_LEFT));
  f32 acceleration = p->mover.on_ground ? GROUND_ACCELERATION : AIR_ACCELERATION;
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
  if (is_key_click(KEY_Z)) p->jump_buffer_timer = JUMP_BUFFER_TIMER_MAX;
  if (p->jump_buffer_timer > 0) p->jump_buffer_timer -= dt;
  if (p->mover.on_ground) p->coyote_timer = COYOTE_TIMER_MAX;
  if (p->coyote_timer > 0) p->coyote_timer -= dt;
  if (p->jump_buffer_timer > 0 && p->coyote_timer > 0) {
    p->variable_jump_timer = VARIABLE_JUMP_TIMER_MAX;
    p->jump_buffer_timer = 0;
    p->coyote_timer = 0;
  }
  if (p->variable_jump_timer > 0) {
    if (!is_key_down(KEY_Z)) p->variable_jump_timer = 0;
    p->mover.velocity.y = JUMP_VELOCITY;
    p->variable_jump_timer -= dt;
  }
  p->mover.weight = p->mover.velocity.y < 0 ? JUMPING_WEIGHT : FALLING_WEIGHT;
  /* update components */
  update_animator(&p->animator, SPR_TEST_FRAMES, g_spr_test_frame_duration, dt);
  update_mover(&p->mover, dt);
}

void
player_render(Entities *e) {
  Player *p = &e->player;
  draw_animator(p->animator, p->mover.collider.position, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)g_spr_test_pixels, 3);
}
