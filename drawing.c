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

void drawTriangleFlatTop(void* vpixels, int width, int height, Vector3d* positions, Color* colors) {
	int* pixels = (int*)vpixels;
	float m0 = (positions[2].y - positions[0].y) / (positions[2].x - positions[0].x);
	float m1 = (positions[2].y - positions[1].y) / (positions[2].x - positions[1].x);
	int x0, x1, start = min(height - 1, positions[0].y), end = max(0, positions[2].y);
	for (int y = start; y >= end; --y) {
		x0 = _Round_F_((y - positions[0].y) / m0 + positions[0].x);
		x1 = _Round_F_((y - positions[1].y) / m1 + positions[1].x);
		_SET_HORIZONTAL_LINE(pixels, x1, x0, y, width, height, color_toInteger(colors[0]));
	}
}

void drawTriangleFlatBottom(void* vpixels, int width, int height, Vector3d* positions, Color* colors) {
	int* pixels = (int*)vpixels;
	float m0 = (positions[2].y - positions[0].y) / (positions[2].x - positions[0].x);
	float m1 = (positions[2].y - positions[1].y) / (positions[2].x - positions[1].x);
	int x0, x1, start = min(height - 1, positions[0].y), end = max(0, positions[2].y);
	for (int y = start + 1; y <= end; ++y) {
		x0 = _Round_F_((y - positions[0].y) / m0 + positions[0].x);
		x1 = _Round_F_((y - positions[1].y) / m1 + positions[1].x);
		_SET_HORIZONTAL_LINE(pixels, x0, x1, y, width, height, color_toInteger(colors[0]));
	}
}

void drawing_drawTriangle(void* pixels, int width, int height, Vector3d* positions, Color* colors) {
	Vector3d newPosition[3];

	// sort vertices by pos.y on the Y Axis.
	if (positions[0].y < positions[1].y) {
		vector3_swap(&(positions[0]), &(positions[1]));
	}
	if (positions[1].y < positions[2].y) {
		vector3_swap(&(positions[1]), &(positions[2]));
	}
	if (positions[0].y < positions[1].y) {
		vector3_swap(&(positions[0]), &(positions[1]));
	}

	// judge whether it a flat or uneven triangle is.
	if (positions[0].y == positions[1].y) {
		if (positions[0].x < positions[1].x) {
			vector3_swap(&(positions[0]), &(positions[1]));
		}
		drawTriangleFlatTop(pixels, width, height, positions, colors);
	}
	else if (positions[1].y == positions[2].y) {
		if (positions[1].x > positions[2].x) {
			vector3_swap(&(positions[1]), &(positions[2]));
		}
		newPosition[0] = positions[1];
		newPosition[1] = positions[2];
		newPosition[2] = positions[0];
		drawTriangleFlatBottom(pixels, width, height, newPosition, colors);
	}
	// slice it into two flat triangles.
	else {
		Vector3d insertPoint;
		float m = (positions[2].y - positions[0].y) / (positions[2].x - positions[0].x);
		Vector3d p0_2_p1 = vector3_minus(positions[1], positions[0]);
		insertPoint.y = -vector3_dot(p0_2_p1, vector3_down) / vector3_dot(vector3_down, vector3_down) + positions[0].y;
		insertPoint.x = (insertPoint.y - positions[0].y) / m + positions[0].x;
		if (positions[1].x > positions[2].x) {
			newPosition[0] = insertPoint;
			newPosition[1] = positions[1];
			newPosition[2] = positions[0];
			drawTriangleFlatBottom(pixels, width, height, newPosition, colors);

			newPosition[0] = positions[1];
			newPosition[1] = insertPoint;
			newPosition[2] = positions[2];
			drawTriangleFlatTop(pixels, width, height, newPosition, colors);
		}
		else {
			newPosition[0] = positions[1];
			newPosition[1] = insertPoint;
			newPosition[2] = positions[0];
			drawTriangleFlatBottom(pixels, width, height, newPosition, colors);

			newPosition[0] = insertPoint;
			newPosition[1] = positions[1];
			newPosition[2] = positions[2];
			drawTriangleFlatTop(pixels, width, height, newPosition, colors);
		}
	}
}