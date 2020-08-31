#pragma once

#include <windows.h>
#include <stdio.h>
#include "renderer.h"
#include "math3d.h"
#include <math.h>

void releaseSurface(Surface* surface) {
	if (surface == 0) {
		return;
	}
	SelectObject(surface->hdc, surface->bitmap);
	DeleteObject(surface->bitmap);
	DeleteDC(surface->hdc);
	free(surface);
}

Surface* createSurface(HWND hwnd, int width, int height) {
	Surface* surface = (Surface*)malloc(sizeof(Surface));
	surface->width = width;
	surface->height = height;
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
	SetBkMode(surface->hdc, TRANSPARENT);
	return surface;
}

void clearSurface(Surface* surface) {
	memset(surface->pixels, 0, surface->width * surface->height * sizeof(int));
}

void blitSurfaceToScreen(Surface* surface) {
	HDC hDC = GetDC(surface->hwnd);
	BitBlt(hDC, 0, 0, surface->width, surface->height, surface->hdc, 0, 0, SRCCOPY);
	ReleaseDC(surface->hwnd, hDC);
}

Renderer* srd_init(HWND hwnd, int width, int height) {
	Renderer* rd = (Renderer*)malloc(sizeof(Renderer));
	rd->surface = NULL;
	srd_setSize(rd, hwnd, width, height);
	return rd;
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

void srd_drawline(Surface* surface, Vector3d p0, Vector3d p1, int color) {
	int* pixels = (int*)surface->pixels;
	if (fdistance(p1.y, p0.y) > fdistance(p1.x, p0.x)) {
		if (p1.y < p0.y) {
			vector3_swap(&p0, &p1);
		}
		float rm = (p1.x - p0.x) / (p1.y - p0.y);
		for (int i = p0.y; i <= p1.y; ++i) {
			_SET_PIXEL(pixels, p0.x + (i - p0.y) * rm, i, surface->width, surface->height, color);
		}
	}
	else {
		if (p1.x < p0.x) {
			vector3_swap(&p0, &p1);
		}
		float m = (p1.y - p0.y) / (p1.x - p0.x);
		for (int i = p0.x; i <= p1.x; ++i) {
			_SET_PIXEL(pixels, i, p0.y + (i - p0.x) * m, surface->width, surface->height, color);
		}
	}
}