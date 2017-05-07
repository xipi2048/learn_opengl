#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

#include "shader.h"

using std::cout;
using std::endl;

bool init();
void close();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
bool checkCompile(GLuint shader, const char* name);
bool checkLink(GLuint program);
void draw();

GLFWwindow* window = nullptr;
GLuint VAO; //vertex array object
GLuint VBO; //vertex buffer object
Shader shader;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

int main()
{
	if (!init())
	{

		

		cout << "Press enter to exit" << endl;
		getchar();
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		auto vertexOffsetXPosition = glGetUniformLocation(shader.Program, "offsetX");
		glUniform1f(vertexOffsetXPosition, 0.5f);

		draw();
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

	//Init vertex objects
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	//Bind VBO data to VAO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	shader.InitShader("shader.vs", "shader.frag");

	return true;
}

void close()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void draw()
{
	//Render clear
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Init
	shader.Use();
	glBindVertexArray(VAO);

	//draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Release
	glBindVertexArray(0);

	glfwSwapBuffers(window);
}