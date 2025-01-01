@echo off

set OUT=game
set SRCS=..\src\main.cpp

pushd bin
cl -Zi -W4 -WX -Fe:%OUT% %SRCS%
popd
