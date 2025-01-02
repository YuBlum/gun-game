#include <windows.h>
#include "include/window.h"
#include "include/renderer.h"
#include "include/math.h"

extern "C" int _fltused = 0;

void __stdcall
main(void) {
  Window window;
  setup_random_seed();
  make_window(&window);
  for (u32 y = 0; y < CANVAS_H; y++) {
    for (u32 x = 0; x < CANVAS_W; x++) {
      pixel(x, y, rand32() & 0xf);
    }
  }
  while (window.is_running) {
    frame_begin();
    canvas_to_backbuffer(&window.backbuffer);
    frame_end();
  }
  ExitProcess(0);
}
