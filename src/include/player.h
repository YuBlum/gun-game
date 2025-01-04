#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "include/entities.h"

void player_start(Entities *e, V2i position, bool start_with_jump);
void player_update(Entities *e, f32 dt);
void player_render(Entities *e);

#endif/*_PLAYER_H_*/
