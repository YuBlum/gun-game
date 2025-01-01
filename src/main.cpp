#include <windows.h>
#include "include/window.h"

extern "C" int _fltused;

void __stdcall
main(void) {
  make_window();
  while (window_is_running()) {
    frame_begin();
    frame_end();
  }
  ExitProcess(0);
}
