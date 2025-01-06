#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "include/core.h"
#include "include/math.h"
#include "include/window.h"

enum Fade : u8 {
  FADE_NONE = 0,
  FADE_OUT,
  FADE_IN,
};

struct Renderer {
  u8 canvas[(CANVAS_W >> 2) * CANVAS_H];
  u8 current_palette = 0b11100100;// 3, 2, 1, 0
  Fade fade = FADE_NONE; 
  f32 fade_timer = 0; 
  u8 fade_iter = 0;
};

void make_renderer(Renderer *renderer);
void clear(u8 color);
void pixel(int x, int y, u8 color);
void pixel(V2i position, u8 color);
void rect(int x, int y, u16 w, u16 h, u8 color);
void rect(V2i position, u16 w, u16 h, u8 color);
#ifdef DEBUG
void rect_outline(int x, int y, u16 w, u16 h, u8 color);
void rect_outline(V2i position, u16 w, u16 h, u8 color);
#endif
void color_buffer(int x, int y, u16 buffer_w, u16 buffer_h, u8 *buffer, u8 color);
void color_buffer(V2i position, u16 buffer_w, u16 buffer_h, u8 *buffer, u8 color);
void color_buffer(int x, int y, u16 buffer_w, u16 buffer_h, u8 *buffer, u8 color1, u8 color0);
void color_buffer(V2i position, u16 buffer_w, u16 buffer_h, u8 *buffer, u8 color1, u8 color0);
void fade_out(void);
void fade_in(void);
bool in_fade(void);
void set_palette(u8 new_palette);
void update_renderer(f32 dt);
void canvas_to_backbuffer(Backbuffer *backbuffer);

#endif/*_RENDERER_H_*/
