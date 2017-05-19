#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

#include "shader.h"
#include "SOIL.h"

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
GLuint texture;
Shader shader;

int imageWidth, imageHeight;
unsigned char* image;

GLfloat vertices[] = {
	// Positions // Colors // Texture Coords
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // Top Left
};

int main()
{
	if (!init())
	{
		cout << "Press enter to exit" << endl;
		getchar();
	}

	//Init texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	float borderColor[] = { 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

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

	shader.InitShader("shader.vert", "shader.frag");	

	//Load texture
	image = SOIL_load_image("container.jpg", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Apply texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

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

	glBindTexture(GL_TEXTURE_2D, texture);

	//Init
	shader.Use();	
	glBindVertexArray(VAO);	

	//draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Release
	glBindVertexArray(0);

	glfwSwapBuffers(window);
}