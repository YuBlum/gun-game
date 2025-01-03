@echo off

set OUT=game
set SRCS=..\src\main.cpp ..\src\window.cpp ..\src\renderer.cpp ..\src\math.cpp ..\src\sprite.cpp ..\src\game.cpp ..\src\player.cpp ..\src\mover.cpp ..\src\map.cpp ..\src\collider.cpp
set LIBS=Kernel32.lib User32.lib Gdi32.lib
set DEBUG=true

if %DEBUG% == true (
  set DEFS=-DDEBUG
  set DEBUG_SRC=..\src\debug.cpp
) else (
  set DEFS=
  set DEBUG_SRC=
)
pushd bin
cl -Zi -W4 -WX -GS- -Gs9999999 %DEFS% -Fe:%OUT% %SRCS% %DEBUG_SRC% %LIBS% -link -entry:main -nodefaultlib -subsystem:windows -stack:0x100000,0x100000
popd
