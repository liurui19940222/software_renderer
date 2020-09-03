#pragma once

#include "renderer.h"

Vertex triangle[3] = {
	{{ -1.0f, -1.0f, 0.0f }},
	{{ 1.0f, -1.0f, 0.0f }},
	{{ 0.0f, 1.0f, 0.0f }},
};

Vertex cube[] = {
	{ { 0.50, -0.50, 0.50 }, { 0.00, 0.00, 1.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 0.50, 1.00 } },
	{ { 0.50, 0.50, 0.50 }, { 0.00, 0.00, 1.00 }, { 0.00, 1.00 }, { 1.00, 0.50, 0.50, 1.00 } },
	{ { -0.50, 0.50, 0.50 }, { 0.00, 0.00, 1.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 0.50, 1.00 } },
	{ { 0.50, -0.50, 0.50 }, { 0.00, 0.00, 1.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 0.50, 1.00 } },
	{ { -0.50, 0.50, 0.50 }, { 0.00, 0.00, 1.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 0.50, 1.00 } },
	{ { -0.50, -0.50, 0.50 }, { 0.00, 0.00, 1.00 }, { 1.00, 0.00 }, { 1.00, 0.50, 0.50, 1.00 } },
	{ { 0.50, 0.50, 0.50 }, { 0.00, 1.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 1.00, 0.50 } },
	{ { 0.50, 0.50, -0.50 }, { 0.00, 1.00, 0.00 }, { 0.00, 1.00 }, { 1.00, 0.50, 1.00, 0.50 } },
	{ { -0.50, 0.50, -0.50 }, { 0.00, 1.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 1.00, 0.50 } },
	{ { 0.50, 0.50, 0.50 }, { 0.00, 1.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 1.00, 0.50 } },
	{ { -0.50, 0.50, -0.50 }, { 0.00, 1.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 1.00, 0.50 } },
	{ { -0.50, 0.50, 0.50 }, { 0.00, 1.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 0.50, 1.00, 0.50 } },
	{ { 0.50, 0.50, -0.50 }, { 0.00, 0.00, -1.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 0.50, 0.00 } },
	{ { 0.50, -0.50, -0.50 }, { 0.00, 0.00, -1.00 }, { 0.00, 1.00 }, { 1.00, 0.50, 0.50, 0.00 } },
	{ { -0.50, -0.50, -0.50 }, { 0.00, 0.00, -1.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 0.50, 0.00 } },
	{ { 0.50, 0.50, -0.50 }, { 0.00, 0.00, -1.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 0.50, 0.00 } },
	{ { -0.50, -0.50, -0.50 }, { 0.00, 0.00, -1.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 0.50, 0.00 } },
	{ { -0.50, 0.50, -0.50 }, { 0.00, 0.00, -1.00 }, { 1.00, 0.00 }, { 1.00, 0.50, 0.50, 0.00 } },
	{ { 0.50, -0.50, -0.50 }, { 0.00, -1.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 0.00, 0.50 } },
	{ { 0.50, -0.50, 0.50 }, { 0.00, -1.00, 0.00 }, { 0.00, 1.00 }, { 1.00, 0.50, 0.00, 0.50 } },
	{ { -0.50, -0.50, 0.50 }, { 0.00, -1.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 0.00, 0.50 } },
	{ { 0.50, -0.50, -0.50 }, { 0.00, -1.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 0.50, 0.00, 0.50 } },
	{ { -0.50, -0.50, 0.50 }, { 0.00, -1.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 0.50, 0.00, 0.50 } },
	{ { -0.50, -0.50, -0.50 }, { 0.00, -1.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 0.50, 0.00, 0.50 } },
	{ { -0.50, -0.50, 0.50 }, { -1.00, 0.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 0.00, 0.50, 0.50 } },
	{ { -0.50, 0.50, 0.50 }, { -1.00, 0.00, 0.00 }, { 0.00, 1.00 }, { 1.00, 0.00, 0.50, 0.50 } },
	{ { -0.50, 0.50, -0.50 }, { -1.00, 0.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 0.00, 0.50, 0.50 } },
	{ { -0.50, -0.50, 0.50 }, { -1.00, 0.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 0.00, 0.50, 0.50 } },
	{ { -0.50, 0.50, -0.50 }, { -1.00, 0.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 0.00, 0.50, 0.50 } },
	{ { -0.50, -0.50, -0.50 }, { -1.00, 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 0.00, 0.50, 0.50 } },
	{ { 0.50, -0.50, -0.50 }, { 1.00, 0.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 1.00, 0.50, 0.50 } },
	{ { 0.50, 0.50, -0.50 }, { 1.00, 0.00, 0.00 }, { 0.00, 1.00 }, { 1.00, 1.00, 0.50, 0.50 } },
	{ { 0.50, 0.50, 0.50 }, { 1.00, 0.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 1.00, 0.50, 0.50 } },
	{ { 0.50, -0.50, -0.50 }, { 1.00, 0.00, 0.00 }, { 0.00, 0.00 }, { 1.00, 1.00, 0.50, 0.50 } },
	{ { 0.50, 0.50, 0.50 }, { 1.00, 0.00, 0.00 }, { 1.00, 1.00 }, { 1.00, 1.00, 0.50, 0.50 } },
	{ { 0.50, -0.50, 0.50 }, { 1.00, 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00, 0.50, 0.50 } },
};