#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"
#include "math3d.h"
#include "geometry.h"

void init() {
	Matrix4x4 m1, m2, m3;
	matrix_makeIdentity(&m1);
	matrix_makeIdentity(&m2);
	m2.m[0][3] = 1;
	m2.m[1][3] = 2;
	m2.m[2][3] = 3;
	matrix_multiply(&m1, &m2, &m3);

	Vector3d euler = { 20, 90, 45 };
	Matrix4x4 rotate;
	matrix_rotate(euler, &rotate);
}

float angle = 0;

void render(Renderer* rd) {
	float halfW = rd->surface->width * 0.5f, halfH = rd->surface->height * 0.5f;
	float aspect = halfW / halfH;
	angle += 0.016f;

	Vector3d eyePos = { 0.0f, 5.0f, -10.0f };
	Vector3d eyeForward = { 0.0f, -0.5f, 1.0f };
	Vector3d eyeUpward = { 0.0f, 1.0f, 0.0f };
	Matrix4x4 m, v, p;
	matrix_rotateY(angle, &m);
	matrix_view(eyePos, eyeForward, eyeUpward, &v);
	matrix_perspective(45, aspect, 0.0f, 100.0f, &p);
	//matrix_ortho2d(1.0f, aspect, 1.0f, 0.1f, &p);
	srd_setMVP(rd->context, &m, &v, &p);

	int triangleSize = sizeof(Vertex) * 3;
	int triCount = sizeof(cube) / triangleSize;
	for (int i = 0; i < triCount; ++i) {
		srd_drawTriangle(rd, cube + i * 3);
	}
}
