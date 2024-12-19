// LearnOpenGl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ServiceLocator.h"
#include "Window.h"
#include "Events.h"
#include "Shader.h"
#include "Assets.h"
#include "Vertex.h"
#include "Mesh.h"
#include "ObjParser.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma comment( lib, "glew32.lib" )
#pragma comment( lib, "glfw3.lib" )
#pragma comment (lib, "OpenGL32.lib")

const int WIDTH = 1280;
const int HEIGHT = 720;

vector<Vertex> vertices = {
    {{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f},  {1.0f,  1.0f}},
    {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f},  {1.0f,  0.0f}},
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f},  {0.0f,  0.0f}},
    {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f},  {0.0f,  1.0f}}
};

vector<vector<unsigned int>> indicesLayers = {
    {0, 1, 3},   // first triangle
    {1, 2, 3}    // second triangle
};

int main(int argc, char** argv)
{
    Window* window = new Window();
    Events* events = new Events();
    Assets* assets = new Assets(argv[0]);

    ServiceLocator servicelLocator{};

    window->Initialize(WIDTH, HEIGHT, "Window");
    servicelLocator.RegisterInstance(window);

    events->Initialize();
    servicelLocator.RegisterInstance(events);

    servicelLocator.RegisterInstance(assets);

    Shader ourShader("shader.vs", "shader.fs");

    glClearColor(0.6f, 0.62f, 0.65f, 1);
    
    ObjParser* objParser = new ObjParser();

    objParser->TryParse("TempHexModel.obj", vertices, indicesLayers);

    Mesh mesh(vertices, indicesLayers);

    glm::mat4 projection;
    glm::mat4 view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    while (window->IsShouldClose() == false)
    {
        events->PullEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        mesh.Draw(0);

        if (events->JustPressed(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(0.8f, 0.4f, 0.2f, 1);
        }
        else if (events->Pressed(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(0.2f, 0.4f, 0.8f, 1);
        }
        else if (events->JustReleased(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(0.2f, 0.8f, 0.2f, 1);
        }
        else
        {
            glClearColor(0.6f, 0.62f, 0.65f, 1);
        }

        window->SwapBuffers();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
