#include "Shader.h"
#include <glad/glad.h>

struct ShaderSource {
	std::string vertexSource;
	std::string fragmentSource;
};

Shader::Shader(const std::string& filePath) {

	enum ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	// Get shaders source code
	int type = ShaderType::NONE;
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	ShaderSource src = { ss[ShaderType::VERTEX].str(), ss[ShaderType::FRAGMENT].str()};

	// Shader compilation

	unsigned int vertex, fragment;
	const char* vertexSource = src.vertexSource.c_str();
	const char* fragmentSource = src.fragmentSource.c_str();
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	glValidateProgram(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vertex);
	glAttachShader(m_RendererID, fragment);
	glLinkProgram(m_RendererID);

	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_RendererID, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(m_RendererID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::set4Float(const std::string& name, float first, float second, float third, float fourth) const {
	glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), first, second, third, fourth);
}