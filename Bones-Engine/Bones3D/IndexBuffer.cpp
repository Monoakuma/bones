#include "IndexBuffer.h"
#include "renderer.h"
#include <GL/glew.h>
/*
unsigned int buffer;

glEnableVertexAttribArray(0);
*/

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: icount(count)
{
	ASK(sizeof(unsigned int) == sizeof(GLuint),"IndexBuffer INIT");
	
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}
void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}