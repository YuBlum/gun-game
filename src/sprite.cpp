#include "include/sprite.h"
#include "include/renderer.h"

void
update_sprite(Sprite *sprite, u32 frames_amount, u16 *frames_duration, f32 dt) {
  sprite->timer += u16(dt * 1000);
  if (sprite->timer > frames_duration[sprite->frame]) {
    sprite->frame = (sprite->frame + 1) % frames_amount;
    sprite->timer = 0;
  }
}

void
draw_sprite(Sprite sprite, int x, int y, u16 width, u16 height, u8 *colors) {
  color_buffer(x, y, width, height, &colors[sprite.frame * (width >> 1) * height]);
}
