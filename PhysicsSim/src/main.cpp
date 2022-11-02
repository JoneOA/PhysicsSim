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

int noOfShapes = 10;

// TODO: Tidy main function, abstract into Application.cpp
std::vector<Shape*> squares;
std::vector<float> vertexAr;
std::vector<unsigned int> indexAr;

void SpawnCube(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xPos = 0, yPos = 0;
        glfwGetCursorPos(window, &xPos, &yPos);

        yPos = 1080 - yPos;

        Square *s = new Square(xPos, yPos, 0);
        std::cout << xPos << ", " << yPos << "\n";

        squares.push_back(s);

        for (int i = 0; i < s->vertexPos.size(); i++)
        {
            vertexAr.push_back(s->vertexPos[i]);
        }

        for (int i = 0; i < s->indexPos.size(); i++)
        {
            indexAr.push_back(s->indexPos[i] + 4 * (squares.size() - 1));
        } 
    }
}

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
    
    glfwSetMouseButtonCallback(window, SpawnCube);
    
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    std::cout << "[INFO] OPENGL VERSION - " << glGetString(GL_VERSION) << std::endl;

    Collision c;

    Physics physics(c);

    //TODO: Shape generator and vertex/index buffer loading 

    for (int i = 0; i < noOfShapes; i++)
    {
        squares.push_back(new Square(i * 0.1, i * 0.05));
    }

    int noOfSquares = squares.size();

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

    glm::mat4 mvp = proj * view * model;

    Shader shader("res/shaders/Basic.glsl");
    shader.Bind();

    shader.SetUniformMat4f("u_MVP", mvp);

    int64_t runTime = 0, currTime, frameTime, accumulator = 0, dt = 1000;
        
    currTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    int lastSquares = noOfSquares;

    /* Loop until the user closes the window */
     while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        noOfSquares = squares.size();
 
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

        if (lastSquares != noOfSquares)
        {
            vb.AddObject(&vertexAr[0], vertexAr.size() * sizeof(float));
            ib.AddObject(&indexAr[0], indexAr.size() * sizeof(unsigned int));
        }

        vb.Update(squares);

        //va.UpdateArray(vb, layout);

        renderer.Draw(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        lastSquares = noOfSquares;
    }

    shader.~Shader();
    glfwTerminate();
    return 0;
}