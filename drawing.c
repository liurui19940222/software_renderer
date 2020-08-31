#include "drawing.h"
#include "renderer.h"

void drawing_drawline(void* vpixels, int width, int height, Vector3d p0, Vector3d p1, int color) {
	int* pixels = (int*)vpixels;
	if (fdistance(p1.y, p0.y) > fdistance(p1.x, p0.x)) {
		if (p1.y < p0.y) {
			vector3_swap(&p0, &p1);
		}
		float rm = (p1.x - p0.x) / (p1.y - p0.y);
		for (int i = (int)(p0.y + 0.5f); i <= (int)(p1.y + 0.5f); ++i) {
			_SET_PIXEL(pixels, p0.x + (i - p0.y) * rm, i, width, height, color);
		}
	}
	else {
		if (p1.x < p0.x) {
			vector3_swap(&p0, &p1);
		}
		float m = (p1.y - p0.y) / (p1.x - p0.x);
		for (int i = (int)(p0.x + 0.5f); i <= (int)(p1.x + 0.5f); ++i) {
			_SET_PIXEL(pixels, i, p0.y + (i - p0.x) * m, width, height, color);
		}
	}
}