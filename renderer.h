#pragma once

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

