#include "VertexArray.h"
#include "Renderer.h"
#include <glad/glad.h>

VertexArray::VertexArray()
	: m_Stride(0)
{
	GLCall(glGenVertexArrays(1, &m_ID));
	GLCall(glBindVertexArray(m_ID));
}

VertexArray::~VertexArray()
{
}

void VertexArray::AddAttibute(unsigned int position, int vec_size, bool normalized, int stride, unsigned int offset)
{
	// TODO: other types of attribute
	VertexArray::Bind();
	GLCall(glVertexAttribPointer(position, vec_size, GL_FLOAT, normalized, stride * sizeof(float), (const void*)(offset * sizeof(float))));
	VertexArray::Enable(position);
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_ID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::Enable(unsigned int position) const
{
	GLCall(glEnableVertexAttribArray(position));
}

void VertexArray::Disable(unsigned int position) const
{
	GLCall(glDisableVertexAttribArray(position));
}
