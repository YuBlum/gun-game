#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include "include/core.h"

#define WINDOW_S 5
#define WINDOW_W (CANVAS_W * WINDOW_S)
#define WINDOW_H (CANVAS_H * WINDOW_S)
#define WINDOW_NAME "Game"

#define KEY_UP    (1 << 0)
#define KEY_DOWN  (1 << 1)
#define KEY_LEFT  (1 << 2)
#define KEY_RIGHT (1 << 3)
#define KEY_Z     (1 << 4)
#define KEY_X     (1 << 5)
#define KEY_ESC   (1 << 6)
#define KEY_DEBUG (1 << 7)

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
  bool has_focus;
};

void make_window(Window *window);
f32 frame_begin(void);
void frame_end(void);
bool is_key_down(u8 key);
bool is_key_click(u8 key);
#ifdef DEBUG
#include "include/math.h"
void rect_debug(int x, int y, u16 w, u16 h);
void rect_debug(V2i position, u16 w, u16 h);
#endif

#endif/*_WINDOW_H_*/
