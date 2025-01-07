#include "include/window.h"
#include "include/renderer.h"

static Window *g_window;
static f32 g_frequency;
static LARGE_INTEGER g_last_time;
static u8 g_key_down;
static u8 g_key_prev;

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
      0, 0,
      WINDOW_W,
      WINDOW_H,
      g_window->backbuffer.hdc,
      0, 0,
      SRCCOPY
    );
    EndPaint(window_handle, &ps);
  } break;
  case WM_KEYDOWN:
    switch (wparam) {
    case VK_UP:     g_key_down |= KEY_UP;    break;
    case VK_LEFT:   g_key_down |= KEY_LEFT;  break;
    case VK_DOWN:   g_key_down |= KEY_DOWN;  break;
    case VK_RIGHT:  g_key_down |= KEY_RIGHT; break;
    case 'Z':       g_key_down |= KEY_A;     break;
    case 'X':       g_key_down |= KEY_B;     break;
    case VK_ESCAPE: g_key_down |= KEY_EXIT;  break;
    case VK_F1:     g_key_down |= KEY_DEBUG; break;
    }
    break;
  case WM_KEYUP:
    switch (wparam) {
    case VK_UP:     g_key_down &= ~KEY_UP;    break;
    case VK_LEFT:   g_key_down &= ~KEY_LEFT;  break;
    case VK_DOWN:   g_key_down &= ~KEY_DOWN;  break;
    case VK_RIGHT:  g_key_down &= ~KEY_RIGHT; break;
    case 'Z':       g_key_down &= ~KEY_A;     break;
    case 'X':       g_key_down &= ~KEY_B;     break;
    case VK_ESCAPE: g_key_down &= ~KEY_EXIT;  break;
    case VK_F1:     g_key_down &= ~KEY_DEBUG; break;
    }
    break;
  case WM_SETFOCUS:
    g_window->has_focus = true;
    break;
  case WM_KILLFOCUS:
    g_window->has_focus = false;
    break;
  case WM_MOVE:
    QueryPerformanceCounter(&g_last_time);
    result = DefWindowProcA(window_handle, msg, wparam, lparam);
    break;
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
  DWORD window_style = WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX;
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
  g_window->has_focus = true;
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
  /* timing */
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);
  g_frequency = f32(frequency.QuadPart);
  QueryPerformanceCounter(&g_last_time);
}

f32
frame_begin(void) {
  /* timing */
  LARGE_INTEGER current_time;
  QueryPerformanceCounter(&current_time);
  f32 dt = f32(current_time.QuadPart - g_last_time.QuadPart) / g_frequency;
  QueryPerformanceCounter(&g_last_time);
  /* input */
  g_key_prev = g_key_down;
  /* dispatch messages */
  MSG msg;
  if (!InvalidateRect(g_window->handle, 0, false)) crash("InvalidateRect failed.");
  while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return dt;
}

void
frame_end(void) {
  canvas_to_backbuffer(&g_window->backbuffer);
}

bool
is_key_down(u8 key) {
  return (g_key_down & key) != 0;
}

bool
is_key_click(u8 key) {
  return (g_key_down & key) != 0 && (g_key_prev & key) == 0;
}

#ifdef DEBUG
void
rect_debug(int x, int y, int w, int h) {
  int t = y * WINDOW_S;
  int l = x * WINDOW_S;
  int b = t + h * WINDOW_S - 1;
  int r = l + w * WINDOW_S - 1;
  if (t >= WINDOW_W || b < 0 || l >= WINDOW_H || r < 0) return;
  for (int ry = t; ry <= b; ry++) {
    if (ry < 0) continue;
    if (ry >= WINDOW_W) break;
    if (l >= 0) g_window->backbuffer.pixels[ry * WINDOW_W + l] = 0xff0000;
    if (r < WINDOW_W) g_window->backbuffer.pixels[ry * WINDOW_W + r] = 0xff0000;
    if (ry == t || ry == b) {
      for (int rx = l + 1; rx <= r; rx++) {
        if (rx < 0) continue;
        if (rx >= WINDOW_H) break;
        g_window->backbuffer.pixels[ry * WINDOW_W + rx] = 0xff0000;
      }
    }
  }
}

void
rect_debug(V2i position, int w, int h) {
  rect_debug(position.x, position.y, w, h);
}
#endif
