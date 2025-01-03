#include <windows.h>
#include "include/math.h"

static u32 g_seed;

void
setup_random_seed(void) {
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  g_seed = ft.dwLowDateTime + ft.dwHighDateTime;
}

u32
rand32(void) {
  g_seed ^= g_seed << 13;
  g_seed ^= g_seed >> 17;
  g_seed ^= g_seed << 5;
  return g_seed;
}

f32
approach(f32 start, f32 end, f32 amount) {
  if (start < end) {
    start += amount;
    if (start > end) return end;
  } else {
    start -= amount;
    if (start < end) return end;
  }
  return start;
}
