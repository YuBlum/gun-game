#include "include/renderer.h"

static u8 canvas[(CANVAS_W >> 1) * CANVAS_H];

static constexpr u32 PALETTE[16] = {
  0x000000, 0x1d2b53, 0x7e2553, 0x008751,
  0xab5236, 0x5f574f, 0xc2c3c7, 0xfff1e8,
  0xff004d, 0xffa300, 0xffec27, 0x00e436,
  0x29adff, 0x83769c, 0xff77a8, 0xffccaa,
};

u8
get_buffer_pixel(int x, int y, u16 buffer_half_w, u8 *buffer) {
  return (buffer[y * buffer_half_w + (x >> 1)] >> (4 * (x & 1))) & 0xf;
}

void
set_buffer_pixel(int x, int y, u16 buffer_half_w, u8 *buffer, u8 color) {
  u8 shift = 4 * (x & 1);
  x >>= 1;
  buffer[y * buffer_half_w + x] = (color << shift) | ((0xf0 >> shift) & buffer[y * buffer_half_w + x]);
}

void
pixel(int x, int y, u8 color) {
  if (x < 0 || x >= CANVAS_W || y < 0 || y >= CANVAS_H) return;
  color &= 0b1111;
  set_buffer_pixel(x, y, CANVAS_W >> 1, canvas, color);
}

void
pixel(V2i position, u8 color) {
  pixel(position.x, position.y, color);
}

void
rect(int x, int y, u16 w, u16 h, u8 color) {
  for (int ry = y; ry < y + h; ry++) {
    for (int rx = x; rx < x + w; rx++) {
      pixel(rx, ry, color);
    }
  }
}

void
rect(V2i position, u16 w, u16 h, u8 color) {
  rect(position.x, position.y, w, h, color);
}

void
rect_outline(int x, int y, u16 w, u16 h, u8 color) {
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
rect_outline(V2i position, u16 w, u16 h, u8 color) {
  rect_outline(position.x, position.y, w, h, color);
}

void
color_buffer(int x, int y, u16 buffer_w, u16 buffer_h, u8 *color, u8 transparent_pixel) {
  for (int _y = 0; _y < buffer_h; _y++) {
    for (int _x = 0; _x < buffer_w; _x++) {
      u8 px = get_buffer_pixel(_x, _y, buffer_w >> 1, color);
      if (px != transparent_pixel) pixel(_x + x, _y + y, px);
    }
  }
}

void
color_buffer(V2i position, u16 buffer_w, u16 buffer_h, u8 *color, u8 transparent_pixel) {
  color_buffer(position.x, position.y, buffer_w, buffer_h, color, transparent_pixel);
}

void
clear(u8 color) {
  color &= 0b1111;
  color |= color << 4;
  for (u32 i = 0; i < ((CANVAS_W * CANVAS_H) >> 1); i++) canvas[i] = color;
}

void
canvas_to_backbuffer(Backbuffer *backbuffer) {
  for (u32 y = 0; y < WINDOW_H; y++) {
    for (u32 x = 0; x < WINDOW_W; x++) {
      u32 cx = x / WINDOW_S;
      u32 cy = y / WINDOW_S;
      backbuffer->pixels[y * WINDOW_W + x] = PALETTE[get_buffer_pixel(cx, cy, CANVAS_W >> 1, canvas)];
    }
  }
}
