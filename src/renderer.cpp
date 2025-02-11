#include "include/renderer.h"

#define FADE_SPEED 10.0f

static Renderer *g_renderer;

static constexpr u32 SCREEN_PALETTE[4] = { 0x141414, 0x9c1c28, 0xedae49, 0xebebeb, };

static u8
get_canvas_pixel(int x, int y) {
  return (g_renderer->canvas[y * (CANVAS_W >> 2) + (x >> 2)] >> ((x & 3) * 2)) & 0x3;
}

static void
set_canvas_pixel(int x, int y, u8 color) {
  u8 shift = 2 * (x & 3);
  x >>= 2;
  g_renderer->canvas[y * (CANVAS_W >> 2) + x] = (color << shift) | ((~(3 << shift)) & g_renderer->canvas[y * (CANVAS_W >> 2) + x]);
}

void
make_renderer(Renderer *renderer) {
  g_renderer = renderer;
}

void
pixel(int x, int y, u8 color) {
  if (x < 0 || x >= CANVAS_W || y < 0 || y >= CANVAS_H) return;
  color &= 0b1111;
  set_canvas_pixel(x, y, color);
}

void
pixel(V2i position, u8 color) {
  pixel(position.x, position.y, color);
}

void
rect(int x, int y, int w, int h, u8 color) {
  for (int ry = y; ry < y + h; ry++) {
    for (int rx = x; rx < x + w; rx++) {
      pixel(rx, ry, color);
    }
  }
}

void
rect(V2i position, int w, int h, u8 color) {
  rect(position.x, position.y, w, h, color);
}

void
rect_outline(int x, int y, int w, int h, u8 color) {
  for (int ry = y; ry < y + h; ry++) {
    pixel(x, ry, color);
    pixel(x + w - 1, ry, color);
    if (ry == y || ry == y + h - 1) {
      for (int rx = x + 1; rx < x + w - 1; rx++) {
        pixel(rx, ry, color);
      }
    }
  }
}

void
rect_outline(V2i position, int w, int h, u8 color) {
  rect_outline(position.x, position.y, w, h, color);
}

void
color_buffer(int x, int y, int buffer_w, int buffer_h, u8 *buffer, u8 color, bool flip) {
  for (int _y = 0; _y < buffer_h; _y++) {
    for (int _x = 0; _x < buffer_w; _x++) {
      int __x = flip ? buffer_w - 1 - _x : _x;
      u8 px = (buffer[_y * (buffer_w >> 3) + (__x >> 3)] >> (__x & 7)) & 1;
      if (px) pixel(_x + x, _y + y, color);
    }
  }
}

void
color_buffer(int x, int y, int buffer_w, int buffer_h, u8 *buffer, u8 color1, u8 color0, bool flip) {
  for (int _y = 0; _y < buffer_h; _y++) {
    for (int _x = 0; _x < buffer_w; _x++) {
      int __x = flip ? buffer_w - 1 - _x : _x;
      u8 px = (buffer[_y * (buffer_w >> 3) + (__x >> 3)] >> (__x & 7)) & 1;
      pixel(_x + x, _y + y, px ? color1 : color0);
    }
  }
}

void
color_buffer(V2i position, int buffer_w, int buffer_h, u8 *buffer, u8 color, bool flip) {
  color_buffer(position.x, position.y, buffer_w, buffer_h, buffer, color, flip);
}

void
color_buffer(V2i position, int buffer_w, int buffer_h, u8 *buffer, u8 color1, u8 color0, bool flip) {
  color_buffer(position.x, position.y, buffer_w, buffer_h, buffer, color1, color0, flip);
}

void
clear(u8 color) {
  color &= 0b1111;
  color |= color << 4;
  for (u32 i = 0; i < ((CANVAS_W * CANVAS_H) >> 2); i++) g_renderer->canvas[i] = color;
}

void
fade_out(void) {
  g_renderer->fade = FADE_OUT;
  g_renderer->fade_iter = 0;
  g_renderer->fade_timer = 0.0f;
}

void
fade_in(void) {
  g_renderer->fade = FADE_IN;
  g_renderer->fade_iter = 3;
  g_renderer->fade_timer = 0.0f;
}

bool
in_fade(void) {
  return g_renderer->fade != FADE_NONE;
}

void
set_palette(u8 new_palette) {
  g_renderer->current_palette = new_palette;
}

void
update_renderer(f32 dt) {
  if (g_renderer->fade != FADE_NONE) {
    g_renderer->fade_timer += FADE_SPEED * dt;
    if (g_renderer->fade_timer >= 1.0f) {
      g_renderer->fade_timer = 0.0f;
      switch (g_renderer->fade) {
      case FADE_OUT:
        if (g_renderer->fade_iter < 3) g_renderer->fade_iter++;
        else g_renderer->fade = FADE_NONE;
        break;
      case FADE_IN:
        if (g_renderer->fade_iter > 0) g_renderer->fade_iter--;
        else g_renderer->fade = FADE_NONE;
        break;
      }
    }
  }
  switch (g_renderer->fade_iter) {
  case 0: g_renderer->current_palette = 0b11100100; break;
  case 1: g_renderer->current_palette = 0b10010000; break;
  case 2: g_renderer->current_palette = 0b01000000; break;
  case 3: g_renderer->current_palette = 0b00000000; break;
  }
}

void
canvas_to_backbuffer(Backbuffer *backbuffer) {
  for (u32 y = 0; y < WINDOW_H; y++) {
    for (u32 x = 0; x < WINDOW_W; x++) {
      u32 cx = x / WINDOW_S;
      u32 cy = y / WINDOW_S;
      backbuffer->pixels[y * WINDOW_W + x] = SCREEN_PALETTE[(g_renderer->current_palette >> (get_canvas_pixel(cx, cy) * 2)) & 3];
    }
  }
}
