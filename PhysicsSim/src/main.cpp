#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include <iostream>
#include <fstream>
#include <string>

#include <sstream>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

#include "Square.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */  
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 1080, "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    std::cout << "[INFO] OPENGL VERSION - " << glGetString(GL_VERSION) << std::endl;

    Square sq(1.0f, 1.0f);

    VertexArray va;
    VertexBuffer vb(sq.vertexPos, sizeof(sq.vertexPos));
    VertexBufferLayout layout;

    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(sq.indexPos, sizeof(sq.indexPos));

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f);


    Renderer renderer;
    
    Shader shader("res/shaders/Basic.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.4f, 0.5f, 1.0);

    shader.SetUniformMat4f("u_MVP", proj);

    float t = 0;

    /* Loop until the user closes the window */
     while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        renderer.Draw(va, ib, shader);

        shader.SetUniform4f("u_Color", sin(t) / 2 + 0.5f, cos(t) / 2 + 0.5f, 0.5f, 1.0f);
        t += 0.01f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

     //shader.~Shader();
    glfwTerminate();
    return 0;
}