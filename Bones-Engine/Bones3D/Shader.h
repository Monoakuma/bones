#pragma once
#include <string>
#include <unordered_map>
class Shader
{ //this class represents a compiled shader
private:
	unsigned int rendererID;
	std::unordered_map<std::string, unsigned int> uniformCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	unsigned int getID() const;

	void Bind() const;
	void Unbind() const;

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform3f(const std::string & name, float v0, float v1, float v2);
	void setUniform2f(const std::string & name, float v0, float v1);
	void setUniform1f(const std::string & name, float v0);
	unsigned int getUniformLocation(const std::string & name);
};