#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "include/types.h"


#ifdef DEBUG
#  define LOG(...) __debug_log(__VA_ARGS__)
void __debug_log(const char *str);
void __debug_log(bool x, bool new_line = true);
void __debug_log(u64 x, bool new_line = true);
void __debug_log(i64 x, bool new_line = true);
void __debug_log(u32 x, bool new_line = true);
void __debug_log(i32 x, bool new_line = true);
void __debug_log(f64 x, bool new_line = true);
void __debug_log(f32 x, bool new_line = true);
void debug_update(void);
extern bool show_colliders;
#else
#  define LOG(...)
#endif



#endif/*_DEBUG_H_*/
