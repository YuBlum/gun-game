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
draw_animator(Animator animator, int x, int y, int width, int height, u8 *pixels, u8 color, bool flip) {
  color_buffer(x, y, width, height, &pixels[animator.frame * (width >> 3) * height], color, flip);
}

void
draw_animator(Animator animator, int x, int y, int width, int height, u8 *pixels, u8 color1, u8 color0, bool flip) {
  color_buffer(x, y, width, height, &pixels[animator.frame * (width >> 3) * height], color1, color0, flip);
}

void
draw_animator(Animator animator, V2i position, int width, int height, u8 *pixels, u8 color, bool flip) {
  draw_animator(animator, position.x, position.y, width, height, pixels, color, flip);
}

void
draw_animator(Animator animator, V2i position, int width, int height, u8 *pixels, u8 color1, u8 color0, bool flip) {
  draw_animator(animator, position.x, position.y, width, height, pixels, color1, color0, flip);
}
