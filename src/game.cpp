#include "include/game.h"
#include "include/renderer.h"
#include "include/player.h"
#include "include/debug.h"
#include "include/map.h"

void
game_start(Entities *e) {
  *e = {};
  map_system_start(e);
}

void
game_update(Entities *e, f32 dt) {
  map_system_update(e);
  if (in_map_transition()) return;
  player_update(e, dt);
#if DEBUG
  debug_update();
#endif
}

void
game_render(Entities *e) {
  clear(0);
  debug_render_map();
  player_render(e);
}
