#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{   
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Update(const std::vector<Shape*>& shapes)
{
    for (int i = 0; i < shapes.size(); i++)
    {
        UpdateBuffer(&shapes[i]->vertexPos[0], 8 * sizeof(float), sizeof(float) * 8 * i);
    }
}

void VertexBuffer::UpdateBuffer(const void* data, unsigned int size, unsigned int offset) {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
