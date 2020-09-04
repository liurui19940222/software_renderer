#pragma once

#include <windows.h>
#include "math3d.h"

typedef struct S_Vertex {
	Vector3d position;
	Vector3d normal;
	Vector2d uv;
	Color color;
} Vertex;

typedef struct S_Fragment {
	Vector3d worldPosition;
	Vector3d worldNormal;
	Vector3d uv;
	Color color;
} Fragment;

typedef struct S_Surface
{
	int width, height;
	float halfWidth, halfHeight;
	HWND hwnd;
	HDC hdc;
	HBITMAP bitmap;
	HBITMAP backBitmap;
	int* pixels;
	float* zbuffer;
} Surface;

enum RenderState
{
	SRD_WIRE_MODE = 1,
	SRD_ZTest = 2,
	SRD_ZWrite = 4,
};

typedef struct S_RenderingContext {
	Matrix4x4 mvp;
	int state;
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

void srd_setMVP(RenderingContext* context, Matrix4x4* m, Matrix4x4* v, Matrix4x4* p);

void srd_enable(RenderingContext* context, int state);

void srd_disable(RenderingContext* context, int state);

BOOL srd_isEnabled(RenderingContext* context, int state);

