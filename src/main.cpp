#include <windows.h>
#include "include/window.h"
#include "include/renderer.h"
#include "include/math.h"
#include "include/game.h"

extern "C" int _fltused = 0;

void __stdcall
main(void) {
  Window window;
  setup_random_seed();
  make_window(&window);
  game_start();
  while (window.is_running) {
    f32 dt = frame_begin();
    if (is_key_down(KEY_ESC)) window.is_running = false;
    game_update(dt);
    game_render();
    frame_end();
  }
  ExitProcess(0);
}
