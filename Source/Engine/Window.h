#pragma once

struct GLFWwindow;


class Window
{
public:
	void Init();
	bool ShouldClose();

	GLFWwindow* mWindow;
};

