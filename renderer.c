#pragma once

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "renderer.h"
#include "math3d.h"
#include "pipeline.h"

#pragma region Helper

void releaseSurface(Surface* surface) {
	if (surface == 0) {
		return;
	}
	SelectObject(surface->hdc, surface->bitmap);
	DeleteObject(surface->bitmap);
	DeleteDC(surface->hdc);
	if (surface->zbuffer != NULL) {
		free(surface->zbuffer);
	}
	free(surface);
}

void clearSurface(Surface* surface) {
	memset(surface->pixels, 0, surface->width * surface->height * sizeof(int));
	if (surface->zbuffer) {
		for (int i = 0; i < surface->width * surface->height; ++i) {
			surface->zbuffer[i] = FLT_MAX;
		}
	}
}

void blitSurfaceToScreen(Surface* surface) {
	HDC hDC = GetDC(surface->hwnd);
	BitBlt(hDC, 0, 0, surface->width, surface->height, surface->hdc, 0, 0, SRCCOPY);
	ReleaseDC(surface->hwnd, hDC);
}

#pragma endregion

Surface* createSurface(HWND hwnd, int width, int height) {
	Surface* surface = (Surface*)malloc(sizeof(Surface));
	surface->width = width;
	surface->height = height;
	surface->halfWidth = width * 0.5f;
	surface->halfHeight = height * 0.5f;
	surface->hwnd = hwnd;
	surface->hdc = CreateCompatibleDC(NULL);
	BITMAPINFOHEADER bmphdr = { 0 };
	bmphdr.biSize = sizeof(BITMAPINFOHEADER);
	bmphdr.biWidth = width;
	bmphdr.biHeight = -height;
	bmphdr.biPlanes = 1;
	bmphdr.biBitCount = 32;
	surface->bitmap = CreateDIBSection(NULL, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS, &(surface->pixels), NULL, 0);
	surface->backBitmap = (HBITMAP)SelectObject(surface->hdc, surface->bitmap);
	surface->zbuffer = (float*)malloc(width * height * sizeof(float));
	SetBkMode(surface->hdc, TRANSPARENT);
	return surface;
}

Renderer* srd_init(HWND hwnd, int width, int height) {
	Renderer* rd = (Renderer*)malloc(sizeof(Renderer));
	rd->context = (RenderingContext*)malloc(sizeof(RenderingContext));
	memset(rd->context, 0, sizeof(RenderingContext));
	rd->surface = NULL;
	srd_setSize(rd, hwnd, width, height);
	return rd;
}

void srd_release(Renderer* rd) {
	if (rd != NULL) {
		if (rd->context != NULL) {
			free(rd->context);
			rd->context = NULL;
		}
		if (rd->surface != NULL) {
			releaseSurface(rd->surface);
			rd->surface = NULL;
		}
		free(rd);
	}
}

void srd_setSize(Renderer* rd, HWND hwnd, int width, int height) {
	releaseSurface(rd->surface);
	rd->surface = createSurface(hwnd, width, height);
}

void srd_beginFrame(Renderer* rd) {
	clearSurface(rd->surface);
}

void srd_endFrame(Renderer* rd) {
	blitSurfaceToScreen(rd->surface);
}

void srd_setMVP(RenderingContext* context, Matrix4x4* m, Matrix4x4* v, Matrix4x4* p) {
	matrix_mvp(m, v, p, &(context->mvp));
}

void srd_enable(RenderingContext* context, int state) {
	context->state |= state;
}

void srd_disable(RenderingContext* context, int state) {
	context->state = context->state & !state;
}

BOOL srd_isEnabled(RenderingContext* context, int state) {
	return (context->state & state) != 0;
}