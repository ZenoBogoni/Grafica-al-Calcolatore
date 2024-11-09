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
public: 
	unsigned int m_RendererID;

	Shader(const std::string& filePath);
	
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void set4Float(const std::string& name, float first, float second, float third, float fourth) const;
};
#endif

