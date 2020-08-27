#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"

void render(Renderer* rd) {
	int* pixels = rd->surface->pixels;
	SYSTEMTIME time;
	GetLocalTime(&time);
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			pixels[i * 800 + j + time.wMilliseconds % 200] = 0xFF0000;
		}
	}
}