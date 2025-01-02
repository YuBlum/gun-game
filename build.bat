@echo off

set OUT=game
set SRCS=..\src\main.cpp ..\src\window.cpp ..\src\renderer.cpp ..\src\math.cpp ..\src\sprite.cpp ..\src\game.cpp ..\src\player.cpp
set LIBS=Kernel32.lib User32.lib Gdi32.lib

pushd bin
cl -Zi -W4 -WX -GS- -Gs9999999 -Fe:%OUT% %SRCS% %LIBS% -link -entry:main -nodefaultlib -subsystem:windows -stack:0x100000,0x100000
popd
