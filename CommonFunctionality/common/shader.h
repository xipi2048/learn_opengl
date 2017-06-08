#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Shader
{
public:
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath) {
		InitShader(vertexSourcePath, fragmentSourcePath);
	}

	GLuint Program;

	//Constructor reads and builds the shader
	void InitShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	//Use the program
	void Use() {
		glUseProgram(this->Program);
	}
};

void Shader::InitShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		//open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "Cannot read file provided\n" << vertexPath << endl << fragmentPath << endl << endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// ----------------------------------------------------------------------------

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "Vertex compilation failed" << endl << infoLog << endl << endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "Fragment compilation failed" << endl << infoLog << endl << endl;
	}

	// ----------------------------------------------------------------------------

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		cout << "Linking failed" << endl << infoLog << endl << endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
