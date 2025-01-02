#include "include/game.h"
#include "include/renderer.h"
#include "include/player.h"

static Entities entities;

void
game_start(void) {
  player_start(&entities);
}

void
game_update(f32 dt) {
  player_update(&entities, dt);
}

void
game_render(void) {
  clear(0);
  player_render(&entities);
}
