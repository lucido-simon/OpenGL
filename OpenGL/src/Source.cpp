// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "core/Camera.h"
#include "core/Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


int main(void)
{
    Renderer renderer;
    GLFWwindow* window = renderer.Init(960, 540, "Hello world");
    if (!window)
        return -1;

    float positions[] =
    {
       -50.f, -50.f, -50.0f, 0.0f, 0.0f, // FACE
        50.f, -50.f, -50.0f, 1.0f, 0.0f,
        50.f,  50.f, -50.0f, 1.0f, 1.0f,
       -50.f,  50.f, -50.0f, 0.0f, 1.0f,

       -50.f, -50.f, 50.0f, 0.0f, 0.0f, // FOND
        50.f, -50.f, 50.0f, 1.0f, 0.0f,
        50.f,  50.f, 50.0f, 1.0f, 1.0f,
       -50.f,  50.f, 50.0f, 0.0f, 1.0f,

        50.f, -50.f, -50.0f, 0.0f, 0.0f, // DROITE
        50.f, -50.f, 50.0f, 1.0f, 0.0f,
        50.f,  50.f, 50.0f, 1.0f, 1.0f,
        50.f,  50.f, -50.0f, 0.0f, 1.0f,

        -50.f, -50.f, 50.0f, 0.0f, 0.0f, // GAUCHE
        -50.f, -50.f, -50.0f, 1.0f, 0.0f,
        -50.f,  50.f, -50.0f, 1.0f, 1.0f,
        -50.f,  50.f, 50.0f, 0.0f, 1.0f,

       -50.f,  50.f, -50.f, 0.0f, 0.0f,   // DESSUS
        50.f,  50.f, -50.f, 1.0f, 0.0f,
        50.f,  50.f,  50.f, 1.0f, 1.0f,
       -50.f,  50.f,  50.f, 0.0f, 1.0f,

       -50.f,  -50.f, -50.f, 0.0f, 0.0f,   // DESSOUS
        50.f,  -50.f, -50.f, 1.0f, 0.0f,
        50.f,  -50.f,  50.f, 1.0f, 1.0f,
       -50.f,  -50.f,  50.f, 0.0f, 1.0f
    };

    unsigned int indices[]
    {
        0, 1, 2,    //FACE
        2, 3, 0,

        4, 5, 6,    //FOND
        6, 7, 4,

        8, 9, 10,   // DROITE
        10, 11, 8,

        12, 13, 14, // GAUCHE
        14, 15, 12,

        16, 17, 18, // DESSUS
        18, 19, 16,

        20, 21, 22, // DESSOUS
        22, 23, 20
    };


    {
        VertexArray va;
        VertexBuffer vb(positions, 24 * 4 * sizeof(float));
        IndexBuffer ib(indices, 36);

        Camera camera;

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        Model model(va, ib);

        // projection matrix
        glm::mat4 proj = glm::perspective(glm::radians(90.f), 4.0f / 3.0f, 0.1f, 100000.f);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/phone.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        float red = 0.0f;
        float step = 0.05f;

        Renderer* rend = new Renderer();
        std::unique_ptr<Renderer> rendPtr = std::make_unique<Renderer>();


        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translationA(0, 0, 0);
        glm::vec3 translationB(400, 200, 0);


        glm::vec3 translationView(0, 0, 0);
        glm::vec3 rotationView(0, 0, 0);


        do
        {
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            camera.setPosition(translationView);
            camera.setRotation(rotationView);

            {
                glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * camera.getViewMatrix() * modelMat;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(model.getVertexArray(), model.getIndexBuffer(), shader);
            }

            {
                glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * camera.getViewMatrix() * modelMat;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(model.getVertexArray(), model.getIndexBuffer(), shader);
            }

            {
                ImGui::SliderFloat3("TranslationA", &translationA.x, -500.0f, 960.0f);
                ImGui::SliderFloat3("TranslationB", &translationB.x, -500.0f, 960.0f);

                ImGui::SliderFloat3("View Translation", &translationView.x, -500, 500);
                ImGui::SliderFloat3("View Rotation", &rotationView.x, -180, 180);


                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }


            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();

            // increment red
            if (red < 0.0f || red > 1.0f)
                step *= -1.0;
            red += step;

        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);
    }

    // Close OpenGL window and terminate GLFW
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}



/*

        while (!glfwWindowShouldClose(window))
        {

            renderer.Clear();
            ImGui_ImplGlfwGL3_NewFrame();

            shader.Bind();
                     
            view = glm::mat4(glm::quatLookAt(glm::radians(rotationView), { 0, 1, 0 })) * glm::mat4(1.f);
            view = glm::translate(view, translationView);

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }
           
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }

            {

                ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat("Depth A", &translationA.z, -10000.f, 100.f);
                ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);

                ImGui::SliderFloat3("View Translation", &translationView.x, -500, 500);
                ImGui::SliderFloat3("View Rotation", &rotationView.x, 0, 360);

                ImGui::SliderFloat("Depth B", &translationB.z, -10000.f, 100.f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }


            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}*/