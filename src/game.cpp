#include "include/game.h"
#include "include/renderer.h"
#include "include/player.h"
#include "include/map.h"

static Entities g_entities;

void
game_start(void) {
  g_entities = {};
  map_system_start(&g_entities);
}

void
game_update(f32 dt) {
  map_system_update(&g_entities, dt);
  if (is_changing_map()) return;
  player_update(&g_entities, dt);
}

void
game_render(void) {
  clear(0);
  debug_render_map();
  player_render(&g_entities);
}
