#pragma once

#include "Shape.h"

class IndexBuffer 
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Update(const std::vector<Shape*>& shapes);

	void UpdateBuffer(const unsigned int* data, unsigned int size, unsigned int offset);

	void AddObject(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};