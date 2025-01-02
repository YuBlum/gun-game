#ifndef _MATH_H_
#define _MATH_H_

#include "include/types.h"

struct V2i { i32 x, y; };
static inline V2i operator +(V2i a, V2i b) { return {a.x + b.x, a.y + b.y}; }
static inline V2i operator -(V2i a, V2i b) { return {a.x - b.x, a.y - b.y}; }
static inline V2i operator *(V2i a, V2i b) { return {a.x * b.x, a.y * b.y}; }
static inline V2i operator /(V2i a, V2i b) { return {a.x / b.x, a.y / b.y}; }
static inline V2i operator +=(V2i &a, V2i b) { a.x += b.x; a.y += b.y; }
static inline V2i operator -=(V2i &a, V2i b) { a.x -= b.x; a.y -= b.y; }
static inline V2i operator *=(V2i &a, V2i b) { a.x *= b.x; a.y *= b.y; }
static inline V2i operator /=(V2i &a, V2i b) { a.x /= b.x; a.y /= b.y; }

void setup_random_seed(void);
u32 rand32(void);

#endif/*_MATH_H_*/
