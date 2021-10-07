#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
	glBindVertexArray(rendererID);
}
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &rendererID);
}
void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
}
void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}