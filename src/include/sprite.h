#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "include/types.h"

struct Sprite {
  u16 timer;
  u16 frame;
};

void update_sprite(Sprite *sprite, u32 frames_amount, u16 *frames_duration, f32 dt);
void draw_sprite(Sprite sprite, int x, int y, u16 width, u16 height, u8 *colors);

#endif/*_SPRITE_H_*/
