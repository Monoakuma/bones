#include "renderer.h"
#include <iostream>
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
void GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << ">> OpenGL Error: 0x" << std::hex << error << std::endl;
	}

}