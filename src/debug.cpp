#include <windows.h>
#include "include/debug.h"

void
__debug_log(char *str) {
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
  while (x) {
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
  while (x) {
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
