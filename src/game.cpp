#include "include/game.h"
#include "include/renderer.h"
#include "include/player.h"
#include "include/map.h"

static Entities g_entities;

void
game_start(void) {
  load_map(&g_entities, 0);
}

void
game_update(f32 dt) {
  player_update(&g_entities, dt);
}

void
game_render(void) {
  clear(0);
  debug_render_map();
  player_render(&g_entities);
}
