#include "include/animator.h"
#include "include/renderer.h"
#include "include/debug.h"

void
update_animator(Animator *animator, u32 frames_amount, u16 *frames_duration, f32 dt) {
  animator->timer += u16(dt * 1000);
  if (animator->timer > frames_duration[animator->frame]) {
    animator->frame = (animator->frame + 1) % frames_amount;
    animator->timer = 0;
  }
}

void
update_animator(Animator *animator, Loop loop, u16 *frames_duration, f32 dt) {
  animator->timer += u16(dt * 1000);
  bool pingpong = animator->pingpong;
  if (animator->timer > frames_duration[animator->frame]) {
    switch (loop.type) {
      case LOOP_FORWARD:
        if (animator->frame == loop.first_frame + loop.amount - 1) {
          animator->frame = loop.first_frame;
        } else {
          animator->frame++;
        }
        break;
      case LOOP_REVERSE:
        if (animator->frame == 0) {
          animator->frame = loop.first_frame + loop.amount - 1;
        } else {
          animator->frame--;
        }
        break;
      case LOOP_PING_PONG_REVERSE:
        pingpong = !animator->pingpong;
      case LOOP_PING_PONG:
        if (pingpong) {
          if (animator->frame == 0) {
            animator->frame++;
            animator->pingpong = !animator->pingpong;
          } else {
            animator->frame--;
          }
        } else {
          if (animator->frame == loop.first_frame + loop.amount - 1) {
            animator->frame--;
            animator->pingpong = !animator->pingpong;
          } else {
            animator->frame++;
          }
        }
        break;
    }
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
