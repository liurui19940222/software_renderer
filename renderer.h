#pragma once

#include <windows.h>
#include "math3d.h"

#define _SET_PIXEL(pixels, x, y, width, height, color) { \
	if (x >= 0 && x < width && y >= 0 && y < height) { \
		pixels[(int)(height - (y + 0.5f)) * width + (int)(x + 0.5f)] = color; \
	}\
}

#define _SET_HORIZONTAL_LINE(pixels, x0, x1, y, width, height, color) { \
	if (x0 < 0) x0 = 0; \
	if (x0 >= width) x0 = width - 1; \
	for (int x = x0; x <= x1; ++x) { \
		pixels[(height - y) * width + x] = color; \
	}\
}

typedef struct S_Vertex {
	Vector3d position;
	Vector3d normal;
	Vector2d uv;
	Vector4d color;
} Vertex;

typedef struct S_Surface
{
	int width, height;
	float halfWidth, halfHeight;
	HWND hwnd;
	HDC hdc;
	HBITMAP bitmap;
	HBITMAP backBitmap;
	void* pixels;
} Surface;

typedef struct S_RenderingContext {
	Matrix4x4 mvp;
	BOOL wireMode;
} RenderingContext;

typedef struct S_Renderer
{
	Surface* surface;
	RenderingContext* context;
} Renderer;

Renderer* srd_init(HWND hwnd, int width, int height);

void srd_release(Renderer* rd);

void srd_setSize(Renderer* rd, HWND hwnd, int width, int height);

void srd_beginFrame(Renderer* rd);

void srd_endFrame(Renderer* rd);

void srd_drawline(Renderer* rd, Vertex v0, Vertex v1, int color);

void srd_drawTriangle(Renderer* rd, Vertex* vertices);

void srd_setMVP(RenderingContext* context, Matrix4x4* m, Matrix4x4* v, Matrix4x4* p);

