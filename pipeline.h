#pragma once

#include "math3d.h"
#include "renderer.h"

void pipe_postLine(Renderer* rd, Vertex* vertices);

void pipe_postMesh(Renderer* rd, Vertex* vertices, int triangleCount);