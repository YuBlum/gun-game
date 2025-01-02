#include "include/player.h"
#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/res/spr-test.h"

#define SPEED 25

void
player_start(Entities *e, V2i position) {
  e->player.mover.position = position;
  e->player.sprite         = {};
}

void
player_update(Entities *e, f32 dt) {
  e->player.mover.velocity.x = f32(is_key_down(KEY_RIGHT) - is_key_down(KEY_LEFT)) * SPEED;
  e->player.mover.velocity.y = f32(is_key_down(KEY_DOWN) - is_key_down(KEY_UP)) * SPEED;
  update_mover(&e->player.mover, dt);
  update_sprite(&e->player.sprite, SPR_TEST_FRAMES, spr_test_frame_duration, dt);
}

void
player_render(Entities *e) {
  draw_sprite(e->player.sprite, e->player.mover.position, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)spr_test_color, 0);
}
