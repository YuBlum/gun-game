#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "include/core.h"
#include "include/window.h"

void clear(u8 color);
void pixel(int x, int y, u8 color);
void rect(int x, int y, u16 w, u16 h, u8 color);
void color_buffer(int x, int y, u16 buffer_w, u16 buffer_h, u8 *color);
void canvas_to_backbuffer(Backbuffer *backbuffer);

#endif/*_RENDERER_H_*/
