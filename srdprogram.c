#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"
#include "math3d.h"

void init() {
	Matrix4x4 m1, m2, m3;
	matrix_makeIdentity(&m1);
	matrix_makeIdentity(&m2);
	m2.m[0][3] = 1;
	m2.m[1][3] = 2;
	m2.m[2][3] = 3;
	matrix_multiply(&m1, &m2, &m3);

	Vector3d euler = { 20, 90, 45 };
	Matrix4x4 rotate;
	matrix_rotate(euler, &rotate);
}

void render(Renderer* rd) {
	//int* pixels = rd->surface->pixels;
	//SYSTEMTIME time;
	//GetLocalTime(&time);
	//for (int i = 0; i < 50; ++i) {
	//	for (int j = 0; j < 50; ++j) {
	//		pixels[i * 800 + j + time.wMilliseconds % 200] = 0xFF0000;
	//	}
	//}
}