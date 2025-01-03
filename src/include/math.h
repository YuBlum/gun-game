#ifndef _MATH_H_
#define _MATH_H_

#include "include/types.h"

struct V2i { i32 x, y; };
static inline V2i operator +(V2i a, V2i b) { return {a.x + b.x, a.y + b.y}; }
static inline V2i operator -(V2i a, V2i b) { return {a.x - b.x, a.y - b.y}; }
static inline V2i operator *(V2i a, V2i b) { return {a.x * b.x, a.y * b.y}; }
static inline V2i operator /(V2i a, V2i b) { return {a.x / b.x, a.y / b.y}; }
static inline V2i operator +(V2i a, i32 b) { return {a.x + b, a.y + b}; }
static inline V2i operator -(V2i a, i32 b) { return {a.x - b, a.y - b}; }
static inline V2i operator *(V2i a, i32 b) { return {a.x * b, a.y * b}; }
static inline V2i operator /(V2i a, i32 b) { return {a.x / b, a.y / b}; }
static inline V2i operator +(i32 a, V2i b) { return {a + b.x, a + b.y}; }
static inline V2i operator -(i32 a, V2i b) { return {a - b.x, a - b.y}; }
static inline V2i operator *(i32 a, V2i b) { return {a * b.x, a * b.y}; }
static inline V2i operator /(i32 a, V2i b) { return {a / b.x, a / b.y}; }
static inline void operator +=(V2i &a, V2i b) { a.x += b.x; a.y += b.y; }
static inline void operator -=(V2i &a, V2i b) { a.x -= b.x; a.y -= b.y; }
static inline void operator *=(V2i &a, V2i b) { a.x *= b.x; a.y *= b.y; }
static inline void operator /=(V2i &a, V2i b) { a.x /= b.x; a.y /= b.y; }
static inline void operator +=(V2i &a, i32 b) { a.x += b; a.y += b; }
static inline void operator -=(V2i &a, i32 b) { a.x -= b; a.y -= b; }
static inline void operator *=(V2i &a, i32 b) { a.x *= b; a.y *= b; }
static inline void operator /=(V2i &a, i32 b) { a.x /= b; a.y /= b; }
static inline V2i operator -(V2i a) { return {-a.x, -a.y}; }

struct V2f { f32 x, y; };
static inline V2f operator +(V2f a, V2f b) { return {a.x + b.x, a.y + b.y}; }
static inline V2f operator -(V2f a, V2f b) { return {a.x - b.x, a.y - b.y}; }
static inline V2f operator *(V2f a, V2f b) { return {a.x * b.x, a.y * b.y}; }
static inline V2f operator /(V2f a, V2f b) { return {a.x / b.x, a.y / b.y}; }
static inline V2f operator +(V2f a, f32 b) { return {a.x + b, a.y + b}; }
static inline V2f operator -(V2f a, f32 b) { return {a.x - b, a.y - b}; }
static inline V2f operator *(V2f a, f32 b) { return {a.x * b, a.y * b}; }
static inline V2f operator /(V2f a, f32 b) { return {a.x / b, a.y / b}; }
static inline V2f operator +(f32 a, V2f b) { return {a + b.x, a + b.y}; }
static inline V2f operator -(f32 a, V2f b) { return {a - b.x, a - b.y}; }
static inline V2f operator *(f32 a, V2f b) { return {a * b.x, a * b.y}; }
static inline V2f operator /(f32 a, V2f b) { return {a / b.x, a / b.y}; }
static inline void operator +=(V2f &a, V2f b) { a.x += b.x; a.y += b.y; }
static inline void operator -=(V2f &a, V2f b) { a.x -= b.x; a.y -= b.y; }
static inline void operator *=(V2f &a, V2f b) { a.x *= b.x; a.y *= b.y; }
static inline void operator /=(V2f &a, V2f b) { a.x /= b.x; a.y /= b.y; }
static inline void operator +=(V2f &a, f32 b) { a.x += b; a.y += b; }
static inline void operator -=(V2f &a, f32 b) { a.x -= b; a.y -= b; }
static inline void operator *=(V2f &a, f32 b) { a.x *= b; a.y *= b; }
static inline void operator /=(V2f &a, f32 b) { a.x /= b; a.y /= b; }
static inline V2f operator -(V2f a) { return {-a.x, -a.y}; }

#define ABS(X) (X < 0 ? -X : X)
#define SIGN(X) (X < 0 ? -1 : 1)

void setup_random_seed(void);
u32 rand32(void);
f32 approach(f32 start, f32 end, f32 amount);

#endif/*_MATH_H_*/
