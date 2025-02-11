#include <windows.h>
#include "include/game.h"
#include "include/debug.h"

extern "C" int _fltused = 0;

void __stdcall
_main(void) {
  Game game;
  setup_random_seed();
  make_window(&game.window);
  make_renderer(&game.renderer);
  game_start(&game.entities);
  while (game.window.is_running) {
    f32 dt = frame_begin();
    if (game.window.has_focus) {
      if (is_key_down(KEY_EXIT)) game.window.is_running = false;
      game_update(&game.entities, dt);
      update_renderer(dt);
    }
    game_render(&game.entities);
    frame_end();
#ifdef DEBUG
    game_debug_render(&game.entities);
#endif
  }
  ExitProcess(0);
}
