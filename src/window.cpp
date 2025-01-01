#include "include/window.h"

static Window *g_window;

static void
crash(char *err) {
  MessageBoxA(0, err, 0, MB_ICONERROR|MB_OK);
  ExitProcess(1);
}

static LRESULT
window_procedure(HWND window_handle, UINT msg, WPARAM wparam, LPARAM lparam) {
  LRESULT result = 0;
  switch (msg) {
  case WM_DESTROY:
  case WM_QUIT:
    g_window->is_running = false;
    break;
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(window_handle, &ps);
    BitBlt(
      hdc,
      ps.rcPaint.left, ps.rcPaint.top,
      ps.rcPaint.right - ps.rcPaint.left,
      ps.rcPaint.bottom - ps.rcPaint.top,
      g_window->backbuffer.hdc,
      0, 0,
      SRCCOPY
    );
    EndPaint(window_handle, &ps);
  } break;
  default:
    result = DefWindowProcA(window_handle, msg, wparam, lparam);
    break;
  }
  return result;
}

void
make_window(Window *window) {
  g_window = window;
  /* create window */
  WNDCLASSA window_class = {};
  window_class.style = CS_HREDRAW|CS_VREDRAW;
  window_class.lpfnWndProc = window_procedure;
  window_class.hInstance = GetModuleHandleA(0);
  window_class.hCursor = LoadCursor(0, IDC_ARROW);
  window_class.lpszClassName = "gun-game-window-class";
  if (!RegisterClassA(&window_class)) crash("RegisterClassA failed.");
  DWORD window_style = WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX;
  RECT window_rect = {0, 0, WINDOW_W, WINDOW_H};
  if (!AdjustWindowRect(&window_rect, window_style, false)) crash("AdjustWindowRect failed.");
  int window_x = CW_USEDEFAULT;
  int window_y = CW_USEDEFAULT;
  RECT screen_rect;
  if (SystemParametersInfoA(SPI_GETWORKAREA, 0, &screen_rect, 0)) {
    auto screen_w = screen_rect.right - screen_rect.left;
    auto screen_h = screen_rect.bottom - screen_rect.top;
    window_x = (screen_w / 2) - (WINDOW_W / 2);
    window_y = (screen_h / 2) - (WINDOW_H / 2);
  }
  g_window->handle = CreateWindowA(
    window_class.lpszClassName,
    WINDOW_NAME,
    window_style,
    window_x,
    window_y,
    window_rect.right - window_rect.left,
    window_rect.bottom - window_rect.top,
    0,
    0,
    window_class.hInstance,
    0
  );
  if (!g_window->handle) crash("CreateWindowA failed.");
  ShowWindow(g_window->handle, SW_SHOW);
  g_window->is_running = true;
  /* create backbuffer */
  g_window->backbuffer.hdc = CreateCompatibleDC(0);
  g_window->backbuffer.info.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
  g_window->backbuffer.info.bmiHeader.biWidth = WINDOW_W;
  g_window->backbuffer.info.bmiHeader.biHeight = -WINDOW_H;
  g_window->backbuffer.info.bmiHeader.biPlanes = 1;
  g_window->backbuffer.info.bmiHeader.biBitCount = 32;
  g_window->backbuffer.info.bmiHeader.biCompression = BI_RGB;
  g_window->backbuffer.bitmap = CreateDIBSection(
    g_window->backbuffer.hdc,
    &g_window->backbuffer.info,
    DIB_RGB_COLORS,
    (void **)&g_window->backbuffer.pixels,
    0,
    0
  );
  if (!g_window->backbuffer.bitmap || !g_window->backbuffer.pixels) crash("CreateDIBSection failed.");
  SelectObject(g_window->backbuffer.hdc, g_window->backbuffer.bitmap);
}

void
frame_begin(void) {
  MSG msg;
  if (!InvalidateRect(g_window->handle, 0, false)) crash("InvalidateRect failed.");
  while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void
frame_end(void) {
  //for (u32 i = 0; i < WINDOW_W * WINDOW_H; i++) g_window->backbuffer.pixels[i] = 0xcc3333;
}
