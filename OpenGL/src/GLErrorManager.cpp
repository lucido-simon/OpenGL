#include "GLErrorManager.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] " << error << " function :" << function << " " << file << " " << line << std::endl;
        return false;
    }

    return true;
}

void GLPrintError()
{
    while (GLenum error = glGetError())
        std::cout << "[OpenGL Error] " << error << std::endl;

}
