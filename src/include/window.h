#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include "include/core.h"

#define WINDOW_S 4
#define WINDOW_W (CANVAS_W * WINDOW_S)
#define WINDOW_H (CANVAS_H * WINDOW_S)
#define WINDOW_NAME "Game"

struct Backbuffer {
  HDC hdc;
  BITMAPINFO info;
  HBITMAP bitmap;
  u32 *pixels;
};

struct Window {
  HWND handle;
  Backbuffer backbuffer;
  bool is_running;
};

void make_window(Window *window);
f32 frame_begin(void);
void frame_end(void);

#endif/*_WINDOW_H_*/
