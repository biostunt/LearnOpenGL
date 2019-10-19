#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


struct openGL {
	GLFWwindow* window;
	int initialize(int width, int height, const char* frame_description);
	void setKeyCallback(GLFWkeyfun f);
	void setBackgroundColor(GLfloat* color);
	void run(void (*f)(GLFWwindow*));
};
