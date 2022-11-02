#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :
    m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{   
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Update(const std::vector<Shape*>& shapes)
{
    std::vector<unsigned int> indexAr;
    for (int i = 0; i < shapes.size(); i++)
    {
        for (int j = 0; j < shapes[i]->indexPos.size(); j++) {
            indexAr.push_back(shapes[i]->indexPos[j] + i * 4);
        }
    }

    std::cout << indexAr.size() / 6 << "\n";
    UpdateBuffer(&indexAr[0], sizeof(indexAr), 0);
}

void IndexBuffer::UpdateBuffer(const unsigned int* data, unsigned int size, unsigned int offset)
{
    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void IndexBuffer::AddObject(const void* data, unsigned int count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_DYNAMIC_DRAW);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
