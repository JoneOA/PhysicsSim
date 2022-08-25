#pragma once

#include <gl/glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Clear() const;

};