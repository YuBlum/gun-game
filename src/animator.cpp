#include "include/animator.h"
#include "include/renderer.h"

void
update_animator(Animator *animator, u32 frames_amount, u16 *frames_duration, f32 dt) {
  animator->timer += u16(dt * 1000);
  if (animator->timer > frames_duration[animator->frame]) {
    animator->frame = (animator->frame + 1) % frames_amount;
    animator->timer = 0;
  }
}

void
draw_animator(Animator animator, int x, int y, u16 width, u16 height, u8 *pixels, u8 color) {
  color_buffer(x, y, width, height, &pixels[animator.frame * (width >> 3) * height], color);
}

void
draw_animator(Animator animator, int x, int y, u16 width, u16 height, u8 *pixels, u8 color1, u8 color0) {
  color_buffer(x, y, width, height, &pixels[animator.frame * (width >> 3) * height], color1, color0);
}

void
draw_animator(Animator animator, V2i position, u16 width, u16 height, u8 *pixels, u8 color) {
  draw_animator(animator, position.x, position.y, width, height, pixels, color);
}

void
draw_animator(Animator animator, V2i position, u16 width, u16 height, u8 *pixels, u8 color1, u8 color0) {
  draw_animator(animator, position.x, position.y, width, height, pixels, color1, color0);
}
