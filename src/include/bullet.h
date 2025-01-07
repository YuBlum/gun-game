#ifndef _BULLET_H_
#define _BULLET_H_

#include "include/entities.h"

void bullet_start(Entities *e);
void bullet_update(Entities *e, f32 dt);
void bullet_render(Entities *e);

#endif/*_BULLET_H_*/
