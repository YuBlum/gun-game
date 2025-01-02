#include <windows.h>
#include "include/window.h"
#include "include/renderer.h"
#include "include/math.h"
#include "include/res/spr-test.h"

extern "C" int _fltused = 0;

void __stdcall
main(void) {
  Window window;
  setup_random_seed();
  make_window(&window);
  f32 x = 0, y = 0;
  while (window.is_running) {
    f32 dt = frame_begin();
    clear(0);
    x += 10 * dt;
    y += 10 * dt;
    color_buffer(int(x), int(y), SPR_TEST_WIDTH, SPR_TEST_HEIGHT, spr_test_color[0]);
    frame_end();
  }
  ExitProcess(0);
}
