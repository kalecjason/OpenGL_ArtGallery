/* Class from learnopengl.com */
#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h> // Include glew to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// The program ID
	GLuint Program;
	// Constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	// Use the program
	void Use();
};

#endif // !SHADER_H