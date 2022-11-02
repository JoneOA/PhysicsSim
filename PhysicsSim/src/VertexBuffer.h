#pragma once

#include <iostream>
#include "Shape.h"
#include <vector>

class VertexBuffer 
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Update(const std::vector<Shape*>& shapes);
	void UpdateBuffer(const void* data, unsigned int size, unsigned int offset);
	void AddObject(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
};

