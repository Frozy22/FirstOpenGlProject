#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

int Window::Initialize(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CURSOR_CAPTURED, GL_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to Initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, width, height);
    return 0;
}

void Window::Terminate() 
{
    glfwTerminate();
}

bool Window::IsShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::SetShouldClose(bool flag)
{
    glfwSetWindowShouldClose(window, flag);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}
