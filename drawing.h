#pragma once

#include "math3d.h"

void drawing_drawline(void* pixels, int width, int height, Vector3d p0, Vector3d p1, int color);

void drawing_drawTriangle(void* pixels, int width, int height, Vector3d* positions, Color* colors);