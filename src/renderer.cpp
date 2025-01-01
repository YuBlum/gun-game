#include "include/renderer.h"

static u8 canvas[(CANVAS_W >> 1) * CANVAS_H];

static constexpr u32 palette[16] = {
  0x000000, 0x1d2b53, 0x7e2553, 0x008751,
  0xab5236, 0x5f574f, 0xc2c3c7, 0xfff1e8,
  0xff004d, 0xffa300, 0xffec27, 0x00e436,
  0x29adff, 0x83769c, 0xff77a8, 0xffccaa,
};

static inline void
unsafe_pixel(int x, int y, u8 color) {
  u8 shift = 4 * (x & 1);
  canvas[y * (CANVAS_W >> 1) + (x >> 1)] = (color << shift) | ((0xf0 >> shift) & canvas[y * (CANVAS_W >> 1) + (x >> 1)]);
}

void
pixel(int x, int y, u8 color) {
  if (x < 0 || x >= CANVAS_W || y < 0 || y >= CANVAS_H) return;
  color &= 0b1111;
  unsafe_pixel(x, y, color);
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
      u8 pixel = (canvas[cy * (CANVAS_W >> 1) + (cx >> 1)] >> (4 * (cx & 1))) & 0xf;
      backbuffer->pixels[y * WINDOW_W + x] = palette[pixel];
    }
  }
}
