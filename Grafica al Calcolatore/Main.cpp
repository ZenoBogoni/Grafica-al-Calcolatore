#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int height = 600;
int width = 600;

int main()
{
	int success;
	char infoLog[512];

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
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

	GLCall(glViewport(0, 0, width, height));

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Shaders
	Shader triangleShader = Shader("res/shaders/triangle.shader");

	// triangle
	float vertices[] = {
		-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f	 // top left
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	unsigned int VAO; // Vertex Array Object
	GLCall(glGenVertexArrays(1, &VAO)); // glGenVertexArrays(how many, &VAO)
	GLCall(glBindVertexArray(VAO)); // bind Vertex Array Object

	VertexBuffer vbo(vertices, sizeof(vertices));
	IndexBuffer ebo(indices, sizeof(indices) / sizeof(unsigned int));

	// Texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// stride: number of bytes between each vertex
	// location 0 position attribute
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0)); // starting, vec* size, type provided, normalized, stride size, pointer inside stride  
	GLCall(glEnableVertexAttribArray(0)); // attribute index
	// location 1 color attribute
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	float redValue, greenValue, blueValue;
	float xDegrees = 120;

	// converting degrees to radians
	float radians = xDegrees * 3.14159 / 180;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		double time = glfwGetTime();
		redValue = sin(time) < 0 ? 0 : sin(time);
		greenValue = sin(time + radians) < 0 ? 0 : sin(time + radians);
		blueValue = sin(time + 2 * radians) < 0 ? 0 : sin(time + 2 * radians);
		GLCall(glClearColor(0.2f, 0.2f, 0.23f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		// Draw the triangle
		triangleShader.use();
		triangleShader.set4Float("myColor", redValue, greenValue, blueValue, 1.0f);
		GLCall(glBindVertexArray(VAO));
		ebo.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
		


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


void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	width = newWidth;
	height = newHeight;
	/*std::cout << "resolution: " << width << "x" << height << std::endl;*/
}

