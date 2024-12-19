#pragma once

#include "IService.h"

struct GLFWwindow;

class Window : public IService
{
private:
	GLFWwindow* window;

public:
	int Initialize(int width, int height, const char* title);
	void Terminate();

	bool IsShouldClose();
	void SetShouldClose(bool flag);

	void SwapBuffers();

	friend class Events;
};

