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

    float positions[8] = {
         0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,

        -0.5f,  0.5f
    };

    unsigned int triInd[] = {
        0, 2, 1,
        0, 1, 3
    };

    float camera[3] = { 0.0f, 0.0f, 0.0f };

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(triInd, sizeof(triInd));
    
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.4f, 0.5f, 1.0);

    float t = 0;

    /* Loop until the user closes the window */
     while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        va.Bind();
        ib.Bind();
        shader.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        t += 0.01f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

     shader.~Shader();
    glfwTerminate();
    return 0;
}