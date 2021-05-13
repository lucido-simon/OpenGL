#pragma once

#include "GLErrorManager.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:

public :
    GLFWwindow* Init(int width, int height, const std::string title);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};