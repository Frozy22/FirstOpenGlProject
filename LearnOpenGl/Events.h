#pragma once

#include <vector>
#include "BitMask.h"
#include "BitMaskExpandable.h"
#include "IService.h"

struct GLFWwindow;

class Events : public IService
{
private:
	static Events* instance;

	ExpandableBitMask _keys;
	ExpandableBitMask _keysJustChanged;

	unsigned long _currentFrame;

	float deltaX;
	float deltaY;

	float x;
	float y;

	bool _cursor_locked;
	bool _cursor_started;

	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
	int Initialize();
	void Terminate();
	void PullEvents();

	bool Pressed(int code);
	bool JustPressed(int code);
	bool JustReleased(int code);
};

