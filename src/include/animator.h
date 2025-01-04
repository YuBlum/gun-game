#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "include/types.h"
#include "include/math.h"

struct Animator {
  u16 timer;
  u16 frame;
};

void update_animator(Animator *animator, u32 frames_amount, u16 *frames_duration, f32 dt);
void draw_animator(Animator animator, int x, int y, u16 width, u16 height, u8 *pixels, u8 color);
void draw_animator(Animator animator, int x, int y, u16 width, u16 height, u8 *pixels, u8 color1);
void draw_animator(Animator animator, V2i position, u16 width, u16 height, u8 *pixels, u8 color);
void draw_animator(Animator animator, V2i position, u16 width, u16 height, u8 *pixels, u8 color1, u8 color0);

#endif/*_ANIMATOR_H_*/
