#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

bool init();
void close();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow *window;

int main()
{
	int returnCode = 0;
	if (!init())
	{
		getchar();
		returnCode = -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //will call key_callback

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	close();
	return returnCode;
}

bool init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	auto glewInitCode = glewInit();
	if (glewInitCode != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;	
		std::cout << glewGetErrorString(glewInitCode) << std::endl;
		return false;
	}

	glViewport(0, 0, 800, 600);
	glfwSetKeyCallback(window, key_callback);

	return true;
}

void close()
{
	glfwTerminate();
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
