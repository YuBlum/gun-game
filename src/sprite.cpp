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
draw_sprite(Sprite sprite, int x, int y, u16 width, u16 height, u8 *pixels, u8 color) {
  color_buffer(x, y, width, height, &pixels[sprite.frame * (width >> 3) * height], color);
}

void
draw_sprite(Sprite sprite, int x, int y, u16 width, u16 height, u8 *pixels, u8 color1, u8 color0) {
  color_buffer(x, y, width, height, &pixels[sprite.frame * (width >> 3) * height], color1, color0);
}

void
draw_sprite(Sprite sprite, V2i position, u16 width, u16 height, u8 *pixels, u8 color) {
  draw_sprite(sprite, position.x, position.y, width, height, pixels, color);
}

void
draw_sprite(Sprite sprite, V2i position, u16 width, u16 height, u8 *pixels, u8 color1, u8 color0) {
  draw_sprite(sprite, position.x, position.y, width, height, pixels, color1, color0);
}
