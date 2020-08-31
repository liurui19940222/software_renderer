#pragma once

#include "math3d.h"

#define _SET_PIXEL(pixels, x, y, width, height, color) { \
	if (x >= 0 && x < width && y >= 0 && y < height) { \
		pixels[(int)(height - (y + 0.5f)) * width + (int)(x + 0.5f)] = color; \
	}\
}

typedef struct S_Surface
{
	int width, height;
	HWND hwnd;
	HDC hdc;
	HBITMAP bitmap;
	HBITMAP backBitmap;
	void* pixels;
} Surface;

typedef struct S_Renderer
{
	Surface* surface;
} Renderer;

Renderer* srd_init(HWND hwnd, int width, int height);

void srd_setSize(Renderer* rd, HWND hwnd, int width, int height);

void srd_beginFrame(Renderer* rd);

void srd_endFrame(Renderer* rd);

void srd_drawline(Surface* surface, Vector3d p0, Vector3d p1, int color);

