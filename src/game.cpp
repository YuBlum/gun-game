#include "include/game.h"
#include "include/renderer.h"
#include "include/player.h"
#include "include/bullet.h"
#include "include/debug.h"
#include "include/map.h"

void
game_start(Entities *e) {
  player_start(e);
  bullet_start(e);
  map_system_start(e);
}

void
game_update(Entities *e, f32 dt) {
  map_system_update(e);
  if (in_map_transition()) return;
  bullet_update(e, dt);
  player_update(e, dt);
#if DEBUG
  debug_update();
#endif
}

void
game_render(Entities *e) {
  clear(0);
  bullet_render(e);
  player_render(e);
}

#if DEBUG
void
game_debug_render(Entities *e) {
  if (!show_colliders) return;
  debug_render_map();
  debug_render_collider(&e->player.collider);
}
#endif
