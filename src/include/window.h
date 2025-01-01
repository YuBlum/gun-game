#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "include/types.h"

#define CANVAS_W 128 
#define CANVAS_H 128 

#define WINDOW_S 4
#define WINDOW_W (CANVAS_W * WINDOW_S)
#define WINDOW_H (CANVAS_H * WINDOW_S)
#define WINDOW_NAME "Game"

void make_window(void);
bool window_is_running(void);
void frame_begin(void);
void frame_end(void);

#endif/*_WINDOW_H_*/
