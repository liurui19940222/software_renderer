#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"
#include "math3d.h"
#include "geometry.h"
#include "input.h"

Vertex* mesh;
int triangleSize = sizeof(Vertex) * 3;
int triCount;

void init() {
	mesh = cube;
	triCount = sizeof(cube) / triangleSize;
}

Vector3d euler = { 0, 0, 0 };

void render(Renderer* rd) {
	float halfW = rd->surface->width * 0.5f, halfH = rd->surface->height * 0.5f;
	float aspect = halfW / halfH;
	euler.x += 0.16f;
	euler.y += 0.16f;
	euler.z += 0.16f;
	
	//if (input_isKeyPressed('A')) {z
	//	angle += 0.16;
	//}
	//if (input_isKeyPressed('D')) {
	//	angle -= 0.16;
	//}

	Vector3d eyePos = { 0.0f, 5.0f, -10.0f };
	Vector3d eyeForward = { 0.0f, -0.5f, 1.0f };
	Vector3d eyeUpward = { 0.0f, 1.0f, 0.0f };
	Matrix4x4 m, v, p;
	matrix_rotate(euler, &m);
	matrix_view(eyePos, eyeForward, eyeUpward, &v);
	matrix_perspective(45, aspect, 0.0f, 100.0f, &p);
	//matrix_ortho2d(1.0f, aspect, 1.0f, 0.1f, &p);
	srd_setMVP(rd->context, &m, &v, &p);
	//rd->context->wireMode = TRUE;

	for (int i = 0; i < triCount; ++i) {
		srd_drawTriangle(rd, mesh + i * 3);
	}
}
