#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Initializer.h";
#include "file_reader.h";
#include "shader.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

_shader* create_shader(const char* path, f_name type) {
	file_reader fr;
	_shader* shader = new _shader(fr.read(path, type));
	return shader;
}

GLuint compile_shader(_shader* shader, unsigned int type) {
	GLuint Shader;
	Shader = glCreateShader(type);
	const char* data = shader->data.c_str();
	glShaderSource(Shader, 1, &data, NULL);
	glCompileShader(Shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return Shader;
}

int create_shader_program(GLuint* shaders, int size) {
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	for (int i = 0; i < size; i++){
		glAttachShader(shaderProgram, shaders[i]);
	}
		
	glLinkProgram(shaderProgram);
	
	
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::ATTACHING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	glUseProgram(shaderProgram);
	for (int i = 0; i < size; i++){
		glDeleteShader(shaders[i]);
	}
	return 0;
}


void Render(GLFWwindow* window) {
	GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLuint shaders[] = {
		compile_shader(create_shader("\\Shaders\\triangle_color.c", PROJECT), GL_FRAGMENT_SHADER),
		compile_shader(create_shader("\\Shaders\\triangle.c", PROJECT), GL_VERTEX_SHADER)
	};
	if (create_shader_program(shaders, 2) != 0) {
		exit(-1);
	}

}


int main(void)
{
	openGL context;
	GLfloat background[] = {
		0.5f, 0.5f, 0.5f, 1.0f
	};

	if (context.initialize(1240, 768, "window") != 0) {
		return -1;
	}
	context.setKeyCallback(key_callback);
	context.setBackgroundColor(background);
	context.run(Render);
	return 0;
}