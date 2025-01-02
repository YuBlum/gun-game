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
