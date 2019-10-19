#include "Initializer.h"


int openGL::initialize(int width, int height, const char* frame_description) {

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	openGL::window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!openGL::window) {
		std::cout << "Failed To create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(openGL::window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW, " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, width, height);
	return 0;
}
void openGL::setKeyCallback(GLFWkeyfun f) {
	glfwSetKeyCallback(openGL::window, f);
}
void openGL::setBackgroundColor(GLfloat* color) {
	glClearColor(color[0], color[1], color[2], color[3]);
}
void openGL::run(void (*f)(GLFWwindow*)) {

	while (!glfwWindowShouldClose(openGL::window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		(*f)(openGL::window);

		glfwSwapBuffers(openGL::window);
	}

}



