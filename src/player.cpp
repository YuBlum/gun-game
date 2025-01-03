#include "include/player.h"
#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/res/spr-test.h"

#define SPEED 50
#define JUMP_HEIGHT -100

void
player_start(Entities *e, V2i position) {
  e->player.mover  = {};
  e->player.sprite = {};
  e->player.mover.collider.position = position;
  e->player.mover.collider.tag      = COL_PLAYER;
}

void
player_update(Entities *e, f32 dt) {
  e->player.mover.velocity.x = f32(is_key_down(KEY_RIGHT) - is_key_down(KEY_LEFT)) * SPEED;
  e->player.mover.velocity.y += GRAVITY * dt;
  if (e->player.mover.velocity.y > GRAVITY_CAP) e->player.mover.velocity.y = GRAVITY_CAP;
  if (is_key_click(KEY_Z)) e->player.mover.velocity.y = JUMP_HEIGHT;
  update_sprite(&e->player.sprite, SPR_TEST_FRAMES, spr_test_frame_duration, dt);
  update_mover(&e->player.mover, dt);
}

void
player_render(Entities *e) {
  draw_sprite(e->player.sprite, e->player.mover.collider.position, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)spr_test_color, 0);
}
