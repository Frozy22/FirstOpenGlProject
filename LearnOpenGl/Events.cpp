#include <GLFW/glfw3.h>
#include <string.h>
#include "Window.h"
#include "Events.h"
#include "ServiceLocator.h"

Events* Events::instance;

void Events::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (instance->_cursor_started)
	{
		instance->deltaX += xpos - instance->x;
		instance->deltaY += ypos - instance->y;
	}
	else 
	{
		instance->_cursor_started = true;
	}

	instance->x = xpos;
	instance->y = ypos;
}

void Events::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) 
	{
		instance->_keys.Set(button, true);
		instance->_keysJustChanged.Set(button, true);
	}
	else if (action == GLFW_RELEASE) 
	{
		instance->_keys.Set(button, false);
		instance->_keysJustChanged.Set(button, true);
	}
}

void Events::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) 
	{
		instance->_keys.Set(key, true);
		instance->_keysJustChanged.Set(key, true);
	}
	else if (action == GLFW_RELEASE) 
	{
		instance->_keys.Set(key, true);
		instance->_keysJustChanged.Set(key, true);
	}
}

int Events::Initialize() 
{
	if (instance != nullptr)
		throw "EVENTS::INITIALIZE::INSTANCE_NOT_NULL";

	instance = this;
	GLFWwindow* window = ServiceLocator::GetInstance()->Resolve<Window>()->window;

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);

	return 0;
}

void Events::Terminate()
{
}

bool Events::Pressed(int code) 
{
	if (code < 0)
		return false;

	return _keys.Get(code);
}

bool Events::JustPressed(int code) 
{
	if (code < 0)
		return false;

	return _keys.Get(code) && _keysJustChanged.Get(code);
}

bool Events::JustReleased(int code)
{
	if (code < 0)
		return false;

	return (_keys.Get(code) == false) && _keysJustChanged.Get(code);
}

void Events::PullEvents() 
{
	_keysJustChanged.Clear();

	deltaX = 0.0f;
	deltaY = 0.0f;

	glfwPollEvents();
}