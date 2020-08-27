#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"
#include "math3d.h"

void init() {
	Matrix4x4 m1, m2, m3;
	matrix_makeIdentity(&m1);
	matrix_makeIdentity(&m2);
	matrix_multiply(&m1, &m2, &m3);
}

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