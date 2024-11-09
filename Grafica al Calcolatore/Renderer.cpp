#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
		return true;

	do {
		std::cout << "[OpenGL Error]: (" << error << ") " << function << " at: " << file << ":" << line << std::endl;
	} while (error = glGetError());
	return false;
}