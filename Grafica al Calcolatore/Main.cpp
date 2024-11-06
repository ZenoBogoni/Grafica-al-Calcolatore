#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	int success;
	char infoLog[512];

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Shaders
	Shader triangleShader = Shader("res/shaders/triangle.shader");

	// triangle
	float vertices[] = { 
		-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int VAO; // Vertex Array Object
	glGenVertexArrays(1, &VAO); // glGenVertexArrays(how many, &VAO)
	glBindVertexArray(VAO); // bind Vertex Array Object

	unsigned int VBO; // create buffer pointer
	glGenBuffers(1, &VBO); // create buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // tell opengl that's our generic array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // tell how big is the buffer, and how it should be used

	// stride: number of bytes between each vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // starting, vec* size, type provided, normalized, stride size, pointer inside stride  
	glEnableVertexAttribArray(0); // attribute index
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	float redValue, greenValue, blueValue;
	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		double time = glfwGetTime();
		redValue = (sin(time) + 1) / 2;
		greenValue = (cos(time + (2 / 3) * 3.14) + 1) / 2;
		blueValue = (sin(time + (4 / 3) * 3.14) + 1) / 2;
		glClearColor(redValue, greenValue, blueValue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		triangleShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // mode, first, count

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

