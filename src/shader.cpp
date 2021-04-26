#include "shader.h"

#include <sstream>
#include <fstream>
#include <string>
#include <windows.h>
#include <glad/glad.h>

const char *vertex = R"()";
const char *fragment = R"()";

std::string ReadFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint CreateShader(const char **src, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, src, nullptr);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char log[2048];
		glGetShaderInfoLog(shader, 2048, 0, log);
		std::stringstream ss;
		switch(type)
		{
			case GL_VERTEX_SHADER:
				ss << "Vertex ";
				break;
			case GL_FRAGMENT_SHADER:
				ss << "Frament ";
				break;
			default:
				ss << "Other ";
		}
		ss << "Shader error:\n" << log;
		MessageBoxA(nullptr, ss.str().c_str(), "Shader compile error", MB_ICONSTOP);
	}
	return shader;
}

Shader::Shader(): program(0)
{}
Shader::~Shader()
{
	glDeleteProgram(program);
}
Shader::Shader(const char *vertex_path, const char *fragment_path): Shader()
{
	LoadShader(vertex_path, fragment_path);
}

int Shader::GetLoc(const char* name)
{
	return glGetUniformLocation(program, name);
}

int Shader::GetAttribLoc(const char* name)
{
	return glGetAttribLocation(program, name);
	GLint a;
}

void Shader::BindAttrib(const char* name, int index)
{
	glBindAttribLocation(program, index, name);
}

void Shader::LoadShader(const char *vertex_path, const char *fragment_path)
{
	const char *vertShaderSrc = vertex;
	const char *fragShaderSrc = fragment;
	std::string vertShaderStr, fragShaderStr;
	if(vertex_path != nullptr && fragment_path != nullptr)
	{
		vertShaderStr = ReadFile(vertex_path);
		fragShaderStr = ReadFile(fragment_path);
		vertShaderSrc = vertShaderStr.c_str();
		fragShaderSrc = fragShaderStr.c_str();
	}

	GLuint myVertexShader = CreateShader(&vertShaderSrc, GL_VERTEX_SHADER);
	GLuint myFragShader = CreateShader(&fragShaderSrc, GL_FRAGMENT_SHADER);

	std::stringstream ss;

	program = glCreateProgram();
	if (program == 0)
		ss << "Shader program creation failed\n";

	glAttachShader(program, myVertexShader);
	glAttachShader(program, myFragShader);
	glLinkProgram(program);
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success)
	{
		char log[2048];
		glGetProgramInfoLog(program, 2048, 0, log);
		ss << "Shader linking error: "<<vertex_path<<" & "<<fragment_path<<":\n" << log <<"\n";
	}

	if(!ss.str().empty())
		MessageBoxA(nullptr, ss.str().c_str(), "Shader program", MB_ICONSTOP);

	glDeleteShader(myVertexShader);
	glDeleteShader(myFragShader);
}

void Shader::Use()
{
	glUseProgram(program);
}