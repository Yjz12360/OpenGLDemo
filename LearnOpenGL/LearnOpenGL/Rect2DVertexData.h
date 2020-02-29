#pragma once

#include "VertexAttr.h"

static const unsigned int rect2DVertexNum = 4;
static const unsigned int rect2DAttribNum = 5;
static const unsigned int rect2DIndexNum = 6;


static const float rect2DVertexData[rect2DVertexNum][rect2DAttribNum] = {
	 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

static const unsigned int rect2DIndexData[rect2DIndexNum] = {
	0,1,3,
	1,2,3
};

#define RECT2D_VERTEX_DATA(index, attr) rect2DVertexData[index][(int)attr]
#define RECT2D_INDEX_DATA(index) rect2DIndexData[index]