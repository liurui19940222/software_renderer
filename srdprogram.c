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
	mesh = triangle;
	triCount = sizeof(triangle) / triangleSize;
}

float angleX = 0;
float angleY = 0;
float angleZ = 0;

void render(Renderer* rd) {
	float halfW = rd->surface->width * 0.5f, halfH = rd->surface->height * 0.5f;
	float aspect = halfW / halfH;
	angleX += 0.16f;
	angleY += 0.16f;
	angleZ += 0.16f;
	
	//if (input_isKeyPressed('A')) {
	//	angle += 0.16;
	//}
	//if (input_isKeyPressed('D')) {
	//	angle -= 0.16;
	//}

	Vector3d eyePos = { 0.0f, 5.0f, -10.0f };
	Vector3d eyeForward = { 0.0f, -0.5f, 1.0f };
	Vector3d eyeUpward = { 0.0f, 1.0f, 0.0f };
	Matrix4x4 m, v, p;
	matrix_rotateXYZ(angleX, angleY, angleZ, &m);
	matrix_view(eyePos, eyeForward, eyeUpward, &v);
	matrix_perspective(45, aspect, 0.0f, 100.0f, &p);
	//matrix_ortho2d(1.0f, aspect, 1.0f, 0.1f, &p);
	srd_setMVP(rd->context, &m, &v, &p);
	//rd->context->wireMode = TRUE;

	for (int i = 0; i < triCount; ++i) {
		srd_drawTriangle(rd, mesh + i * 3);
	}
}
