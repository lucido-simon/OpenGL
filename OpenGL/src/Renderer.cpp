#include "Renderer.h"
#include <iostream>


GLFWwindow* Renderer::Init(int width, int height, const std::string title)
{
   
    /* Initialize the library */
    if (!glfwInit())
        return nullptr;

    GLFWwindow* window = glfwCreateWindow(960, 540, "HelloWorld", NULL, NULL);

    if (!window)
    {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error !" << std::endl;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));   // Enable depth testing for z-culling
    GLCall(glDepthFunc(GL_LESS));    // Set the type of depth-test
    GLCall(glShadeModel(GL_SMOOTH));   // Enable smooth shading
    GLCall(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST));  // Nice perspective corrections

    GLCall(glfwSwapInterval(1));

    GLPrintError();

    return window;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
