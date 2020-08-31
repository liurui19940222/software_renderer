#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"
#include "math3d.h"

Vector3d geometry[3] = {
	{-1.0f, -1.0f, 0.0f},
	{1.0f, -1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f}
};

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
	angle += 0.016;
	Vector3d eyePos = { 0.0f, 0.0f, -10.0f };
	Vector3d eyeForward = { 0.0f, 0.0f, 1.0f };
	Vector3d eyeUpward = { 0.0f, 1.0f, 0.0f };
	Matrix4x4 m, v, p, mvp;
	matrix_rotateZ(angle, &m);
	matrix_view(eyePos, eyeForward, eyeUpward, &v);
	matrix_perspective(45, aspect, 0.0f, 100.0f, &p);
	//matrix_ortho2d(1.0f, aspect, 1.0f, 0.1f, &p);
	matrix_mvp(&m, &v, &p, &mvp);

	Vector3d vertex0, vertex1;
	Vector3d point0, point1;
	int count = sizeof(geometry) / sizeof(Vector3d);
	for (int i = 0; i < count; ++i) {
		vertex0 = geometry[i];
		vertex1 = geometry[(i + 1) % count];
		matrix_transformPoint(&mvp, vertex0, &vertex0);
		matrix_transformPoint(&mvp, vertex1, &vertex1);
		transform_viewport(vertex0, halfW, halfH, &point0);
		transform_viewport(vertex1, halfW, halfH, &point1);
		srd_drawline(rd->surface, point0, point1, 0xFF0000);
	}
}
