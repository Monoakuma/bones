#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include "renderer.h"
#include "Shader.h"
struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

static ShaderSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "failed to compile shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

Shader::Shader(const std::string& filepath)
{
	ShaderSource source = ParseShader(filepath);
	rendererID = CreateShader(source.vertexSource, source.fragmentSource);
}
Shader::~Shader() 
{
	glDeleteProgram(rendererID);
}
unsigned int Shader::getID() const
{
	return rendererID;
}
void Shader::Bind() const
{
	glUseProgram(rendererID);
}
void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUseProgram(rendererID);
	TestCall(glUniform4f(getUniformLocation(name),v0,v1,v2,v3));
}
void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUseProgram(rendererID);
	TestCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}
void Shader::setUniform2f(const std::string& name, float v0, float v1)
{
	glUseProgram(rendererID);
	TestCall(glUniform2f(getUniformLocation(name), v0, v1));
}
void Shader::setUniform1f(const std::string& name, float v0)
{
	glUseProgram(rendererID);
	TestCall(glUniform1f(getUniformLocation(name), v0));
}
unsigned int Shader::getUniformLocation(const std::string& name)
{
	if (uniformCache.find(name) != uniformCache.end()) return uniformCache[name];
	unsigned int location = glGetUniformLocation(rendererID, name.c_str());
	if (location == -1)
		std::cout << "404 MISSING VARIABLE: uniform '" << name << "' was not found" << std::endl;
	uniformCache[name] = location;
	return location; 
}
/*
shader parser 
so something like
uniform double uGetTime;
will be filled with glfwGetTime();

*/