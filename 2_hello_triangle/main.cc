#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

bool init();
void close();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLFWwindow* window = nullptr;
GLuint VBO;
GLuint vertexShader;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.0f, 0.0f
};

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
)";

int main()
{
	if (!init())
	{
		getchar();
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	close();
	return 0;
}

bool init()
{
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "Hello, triangle", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Could not create window" << endl;
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	//Init GLEW
	glewExperimental = GL_TRUE;
	auto glewInitCode = glewInit();
	if (glewInitCode != GLEW_OK)
	{
		cout << "Problem initializing GLEW" << endl
			<< glewGetErrorString(glewInitCode) << endl;
		return false;
	}

	glViewport(0, 0, 800, 600);

	//Init GL Buffers
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Compile shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	return true;
}

void close()
{
	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}