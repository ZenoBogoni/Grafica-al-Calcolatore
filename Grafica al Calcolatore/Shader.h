#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

class Shader
{
private: 
	unsigned int m_RendererID;
	std::string m_FilePath;
public: 
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void setUniform1b(const std::string &name, bool value) const;
	void setUniform1i(const std::string &name, int value) const;
	void setUniform1f(const std::string &name, float value) const;
	void setUniform4f(const std::string& name, float first, float second, float third, float fourth) const;

	inline std::string getFilePath() const { return m_FilePath; }
};
#endif

