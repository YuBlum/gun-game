#include <windows.h>
#include "include/window.h"
#include "include/renderer.h"

extern "C" int _fltused = 0;

void __stdcall
main(void) {
  Window window;
  make_window(&window);
  u16 size = 10;
  f32 x = (CANVAS_W * 0.5f) - (size * 0.5f),
      y = (CANVAS_H * 0.5f) - (size * 0.5f);
  while (window.is_running) {
    frame_begin();
    clear(1);
    x += 0.05f;
    rect(int(x), int(y), size, size, 8);
    canvas_to_backbuffer(&window.backbuffer);
    frame_end();
  }
  ExitProcess(0);
}
