#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include <time.h>

#include <iostream>
#include <fstream>
#include <string>

#include <sstream>

#include <algorithm>

#include <random>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Physics.h"
#include "Collision.h"

#include "Square.h"
#include "Triangle.h"
#include "Cube.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int noOfShapes = 2;

// TODO: Tidy main function, abstract into Application.cpp

int main()
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

    glfwSwapInterval(0);
    
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    std::cout << "[INFO] OPENGL VERSION - " << glGetString(GL_VERSION) << std::endl;

    Collision c;

    Physics physics(c);

    std::vector<float> vertexAr;
    std::vector<unsigned int> indexAr;


    //TODO: Shape generator and vertex/index buffer loading 
    std::vector<Shape*> squares;

    for (int i = 0; i < noOfShapes; i++)
    {
        squares.push_back(new Square(i * 0.2 , i * 0.4));
    }

    for (int i = 0; i < noOfShapes; i++)
    {
        for (int j = 0; j < squares[i]->vertexPos.size(); j++) 
        {
            vertexAr.push_back(squares[i]->vertexPos[j]);
        }
    }

    for (int i = 0; i < noOfShapes; i++) {
        for (int j = 0; j < squares[i]->indexPos.size(); j++) {
            indexAr.push_back(squares[i]->indexPos[j] + i * 4);
        }
    }

    VertexArray va;
    va.Bind();

    VertexBuffer vb(&vertexAr[0], vertexAr.size() * sizeof(float));
    vb.Bind();

    IndexBuffer ib(&indexAr[0], indexAr.size() * sizeof(unsigned int));
    ib.Bind();

    VertexBufferLayout layout;
    Renderer renderer;

    layout.Push<float>(2);

    va.AddBuffer(vb, layout);


    glm::mat4 proj = glm::ortho(0.0f, 1080.0f, 0.0f, 1080.0f, 0.1f, 1080.0f);
    glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    //model = glm::scale(model, glm::vec3(100.0f));

    glm::mat4 mvp = proj * view * model;

    Shader shader("res/shaders/Basic.glsl");
    shader.Bind();

    shader.SetUniformMat4f("u_MVP", mvp);

    int64_t runTime = 0, currTime, frameTime, accumulator = 0, dt = 1000;
        
    currTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    /* Loop until the user closes the window */
     while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
 
        frameTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - currTime;
        currTime += frameTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            physics.OnUpdate(squares, dt);
            accumulator -= dt;
            runTime += dt;
        }
        //TODO: Interpolate "left over" time from accumalator, stretch goal maybe

        c.CheckCollision(*squares[0], *squares[1]);

        vb.Update(squares);

        va.UpdateArray(vb, layout);

        renderer.Draw(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.~Shader();
    glfwTerminate();
    return 0;
}