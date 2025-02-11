#include <windows.h>
#include "include/debug.h"
#include "include/window.h"
#include "include/map.h"

bool show_colliders = false;

void
__debug_log(const char *str) {
  OutputDebugStringA(str);
}

void
__debug_log(bool x, bool new_line) {
  if (new_line) {
    OutputDebugString(x ? "true\n" : "false\n");
  } else {
    OutputDebugString(x ? "true" : "false");
  }
}

void
__debug_log(u64 x, bool new_line) {
  char buf[22];
  u32 index = sizeof (buf) / sizeof (buf[0]) - 1;
  buf[index] = '\0';
  if (new_line) buf[--index] = '\n';
  if (x == 0) {
    buf[--index] = '0';
  } else while (x) {
    buf[--index] = x % 10 + '0';
    x /= 10;
  }
  OutputDebugStringA(&buf[index]);
}

void
__debug_log(i64 x, bool new_line) {
  char buf[23];
  u32 index = sizeof (buf) / sizeof (buf[0]) - 1;
  buf[index] = '\0';
  if (new_line) buf[--index] = '\n';
  bool sign = x < 0;
  x = sign ? -x : x;
  if (x == 0) {
    buf[--index] = '0';
  } else while (x) {
    buf[--index] = x % 10 + '0';
    x /= 10;
  }
  if (sign) buf[--index] = '-';
  OutputDebugStringA(&buf[index]);
}

void
__debug_log(u32 x, bool new_line) {
  __debug_log(u64(x), new_line);
}

void
__debug_log(i32 x, bool new_line) {
  __debug_log(i64(x), new_line);
}

void
__debug_log(f64 x, bool new_line) {
  if (x != x) {
    __debug_log("nan");
    if (new_line) __debug_log("\n");
    return;
  }
  u64 float_part = u64((x - i64(x)) * 1000000);
  __debug_log(i64(x), false);
  __debug_log(".");
  if (float_part < 10) {
    __debug_log("00000");
  } else if (float_part < 100) {
    __debug_log("0000");
  } else if (float_part < 1000) {
    __debug_log("000");
  } else if (float_part < 10000) {
    __debug_log("00");
  } else if (float_part < 100000) {
    __debug_log("0");
  }
  __debug_log(float_part, new_line);
}

void
__debug_log(f32 x, bool new_line) {
  __debug_log(f64(x), new_line);
}

void
debug_update(void) {
  if (is_key_down(KEY_DEBUG)) {
    if (is_key_click(KEY_UP)) reload_map();
    if (is_key_click(KEY_B)) show_colliders = !show_colliders;
  }
}
