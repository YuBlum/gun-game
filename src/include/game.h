#ifndef _GAME_H_
#define _GAME_H_

#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/entities.h"

struct Game {
  Window window;
  Renderer renderer;
  Entities entities;
};

void game_start(Entities *e);
void game_update(Entities *e, f32 dt);
void game_render(Entities *e);

#endif/*_GAME_H_*/
