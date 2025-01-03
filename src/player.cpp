#include "include/player.h"
#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/res/spr-test.h"

#define SPEED 50

void
player_start(Entities *e, V2i position) {
  e->player.mover  = {};
  e->player.sprite = {};
  e->player.mover.collider.position = position;
  e->player.mover.collider.tag      = COL_PLAYER;
}

static f32 g_dt;

void
player_update(Entities *e, f32 dt) {
  g_dt = dt;
  e->player.mover.velocity.x = f32(is_key_down(KEY_RIGHT) - is_key_down(KEY_LEFT)) * SPEED;
  e->player.mover.velocity.y = f32(is_key_down(KEY_DOWN) - is_key_down(KEY_UP)) * SPEED;
  update_sprite(&e->player.sprite, SPR_TEST_FRAMES, spr_test_frame_duration, dt);
  update_mover(&e->player.mover, g_dt);
}

void
player_render(Entities *e) {
  draw_sprite(e->player.sprite, e->player.mover.collider.position, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)spr_test_color, 0);
}
