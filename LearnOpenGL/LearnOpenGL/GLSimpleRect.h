#pragma once

#ifndef GL_SIMPLE_RECT_H
#define GL_SIMPLE_RECT_H

#include "GLObject.h"



class GLSimpleRect : public GLObject {
public:
	GLSimpleRect();/* {

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		shader = new Shader("shader.vs", "shader.fs");
	};*/
	virtual void render(); /*{
		GLObject::render();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	};*/

};
#endif