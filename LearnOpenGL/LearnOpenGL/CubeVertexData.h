#pragma once

#include "VertexAttr.h"

static const unsigned int cubeVertexNum = 24;
static const unsigned int cubeAttribNum = 8;
static const unsigned int cubeIndexNum = 36;

static const float cubeVertexData[cubeVertexNum][cubeAttribNum] = {
	 //pos              uv		   //normal
//front
	 -0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f,
	 -0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f,-1.0f,
	  0.5f, 0.5f,-0.5f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,
	  0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f,
//back
	  0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 -0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//left
	 -0.5f,-0.5f, 0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
	 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,-1.0f, 0.0f, 0.0f,
	 -0.5f, 0.5f,-0.5f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
	 -0.5f,-0.5f,-0.5f, 1.0f, 0.0f,-1.0f, 0.0f, 0.0f,
//right
	  0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	  0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	  0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//top
	 -0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	  0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//bottom
	 -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f,
	 -0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f,
	  0.5f,-0.5f,-0.5f, 1.0f, 1.0f, 0.0f,-1.0f, 0.0f,
	  0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,-1.0f, 0.0f
};

static const unsigned int cubeIndexData[] = {
	0,1,2,0,2,3,
	4,5,6,4,6,7,
	8,9,10,8,10,11,
	12,13,14,12,14,15,
	16,17,18,16,18,19,
	20,21,22,20,22,23
};

#define CUBE_VERTEX_DATA(index, attr) cubeVertexData[index][(int)attr]
#define CUBE_INDEX_DATA(index) cubeIndexData[index]