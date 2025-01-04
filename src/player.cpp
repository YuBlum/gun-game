#include "include/player.h"
#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/debug.h"
#include "include/res/spr-test.h"

#define MAX_SPEED            60.0f
#define GROUND_ACCELERATION  650.0f
#define AIR_ACCELERATION     800.0f
#define FRICTION             650.0f
#define JUMP_VELOCITY       -75.0f
#define JUMP_TIMER_MAX       0.15f
#define JUMPING_WEIGHT       1.50f
#define FALLING_WEIGHT       1.00f

static bool is_fade_in;

void
player_start(Entities *e, V2i position) {
  Player *p = &e->player;
  p->mover  = {};
  p->animator = {};
  p->jump_timer = 0;
  p->mover.weight            = 1.0f;
  p->mover.has_gravity       = true;
  p->mover.collider.tag      = COL_PLAYER;
  p->mover.collider.position = position;
}

void
player_update(Entities *e, f32 dt) {
  Player *p = &e->player;
  f32 input = f32(is_key_down(KEY_RIGHT) - is_key_down(KEY_LEFT));
  f32 acceleration = p->mover.on_ground ? GROUND_ACCELERATION : AIR_ACCELERATION;
  p->mover.velocity.x += input * acceleration * dt;
  if (ABS(p->mover.velocity.x) > MAX_SPEED) {
    p->mover.velocity.x = approach(
      p->mover.velocity.x,
      MAX_SPEED * input,
      1500 * dt
    );
  }
  if (input == 0.0f) p->mover.velocity.x = approach(p->mover.velocity.x, 0, FRICTION * dt);
  if (is_key_click(KEY_Z) && p->mover.on_ground) p->jump_timer = JUMP_TIMER_MAX;
  if (p->jump_timer > 0) {
    if (!is_key_down(KEY_Z)) p->jump_timer = 0;
    p->mover.velocity.y = JUMP_VELOCITY;
    p->jump_timer -= dt;
  }
  p->mover.weight = p->mover.velocity.y < 0 ? JUMPING_WEIGHT : FALLING_WEIGHT;
  update_animator(&p->animator, SPR_TEST_FRAMES, spr_test_frame_duration, dt);
  update_mover(&p->mover, dt);

  if (is_key_click(KEY_DEBUG) && !in_fade()) {
    if (is_fade_in) fade_in();
    else fade_out();
    is_fade_in = !is_fade_in;
  }
}

void
player_render(Entities *e) {
  Player *p = &e->player;
  draw_animator(p->animator, p->mover.collider.position, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)spr_test_pixels, 3);
}
