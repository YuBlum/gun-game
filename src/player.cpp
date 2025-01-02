#include "include/player.h"
#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/res/spr-test.h"

void
player_start(Entities *e) {
  e->player.position = {(CANVAS_W >> 1) - 4, (CANVAS_H >> 1) - 4};
  e->player.sprite   = {};
}

void
player_update(Entities *e, f32 dt) {
  update_sprite(&e->player.sprite, SPR_TEST_FRAMES, spr_test_frame_duration, dt);
}

void
player_render(Entities *e) {
  draw_sprite(e->player.sprite, e->player.position.x, e->player.position.y, SPR_TEST_WIDTH, SPR_TEST_HEIGHT, (u8 *)spr_test_color);
  if (is_key_click(KEY_Z)) OutputDebugStringA("Z\n");
  if (is_key_click(KEY_X)) OutputDebugStringA("X\n");
  if (is_key_click(KEY_UP)) OutputDebugStringA("^\n");
  if (is_key_click(KEY_LEFT)) OutputDebugStringA("<\n");
  if (is_key_click(KEY_RIGHT)) OutputDebugStringA(">\n");
  if (is_key_click(KEY_DOWN)) OutputDebugStringA("v\n");
  if (is_key_click(KEY_ESC)) OutputDebugStringA("esc\n");
  if (is_key_down(KEY_Z)) pixel(0, 0, 1);
  if (is_key_down(KEY_X)) pixel(0, 0, 2);
  if (is_key_down(KEY_UP)) pixel(0, 0, 3);
  if (is_key_down(KEY_LEFT)) pixel(0, 0, 4);
  if (is_key_down(KEY_RIGHT)) pixel(0, 0, 5);
  if (is_key_down(KEY_DOWN)) pixel(0, 0, 6);
  if (is_key_down(KEY_ESC)) pixel(0, 0, 7);
}
