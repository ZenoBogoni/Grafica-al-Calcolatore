#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	void setUniform3f(const std::string& name, float v0, float v1, float v2) const;
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void setUniform3f(const std::string& name, const glm::vec3& vector) const;
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

	inline std::string getFilePath() const { return m_FilePath; }
};
#endif

