#pragma once

#include <windows.h>

void input_init();

void input_setKeyDown(unsigned char keyCode);

void input_setKeyUp(unsigned char keyCode);

BOOL input_isKeyPressed(unsigned char keyCode);