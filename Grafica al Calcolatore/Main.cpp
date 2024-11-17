#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexArray.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


void processInput(GLFWwindow* window);

void updateModel(glm::mat4 traslation = glm::mat4(1.0f));
void updateView();

int SRC_HEIGHT = 600;
int SRC_WIDTH = 1280;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = SRC_WIDTH / 2, lastY = SRC_HEIGHT / 2;
bool firstMouse = true;

glm::mat4 model;
float xAngle = 0.0f;
float yAngle = 0.0f;
float scaleFactor = 1.0f;

glm::mat4 view;
glm::vec3 cameraPosition(0.0f, 0.0, 0.0f);
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection;
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;

unsigned int nCubes = 1;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		std::cin.get();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::cin.get();
		return -1;
	}

	GLCall(glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT));
	// opengl functionalities
	GLCall(glEnable(GL_CULL_FACE));

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));

	//glfwSwapInterval(1); // vsync?
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// MVP
	model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::lookAt( cameraPosition, cameraPosition + cameraFront, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 10000.0f);
	updateModel();


	// Shaders
	Shader shader = Shader("res/shaders/triangle.shader");


	// triangle
	float vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // front bottom left 
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // front bottom right 
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // front top right 
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // front top left 
		// back
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // back bottom right 
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // back bottom left 
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // back top left 
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // back top right 
		 // left
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // left bottom left
		 -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // left bottom right 
		 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // left top right
		 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // left top left 
		 // right
		  0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // right bottom left 
		  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // right bottom right
		  0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // right top right
		  0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // right top left 
		  // top 
		 -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top bottom left
		  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // top bottom right
		  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top top right
		 -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top top left
		 // bottom 
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top bottom left
		  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // top bottom right
		  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top top right
		 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top top left
	};

	// index
	unsigned int indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		4, 5, 6,
		6, 7, 4,
		// left
		8, 9, 10,
		10, 11, 8,
		// right 
		12, 13, 14,
		14, 15, 12,
		// top
		16, 17, 18,
		18, 19, 16,
		// bottom
		20, 21, 22,
		22, 23, 20,
	};

	glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f, 0.0f, 0.0f),
		 glm::vec3(2.0f, 5.0f,-15.0f),
		 glm::vec3(-1.5f,-2.2f,-2.5f),
		 glm::vec3(-3.8f,-2.0f,-12.3f),
		 glm::vec3(2.4f,-0.4f,-3.5f),
		 glm::vec3(-1.7f, 3.0f,-7.5f),
		 glm::vec3(1.3f,-2.0f,-2.5f),
		 glm::vec3(1.5f, 2.0f,-2.5f),
		 glm::vec3(1.5f, 0.2f,-1.5f),
		 glm::vec3(-1.3f, 1.0f,-1.5f)
	};

	// VAO
	VertexArray vao;
	// VBO
	VertexBuffer vbo(vertices, sizeof(vertices));
	// EBO
	IndexBuffer ebo(indices, sizeof(indices) / sizeof(unsigned int));
	// Texture
	Texture grassBlockTexture("assets/textures/minecraft_grass.jpg", GL_RGB);
	Texture shrekSmithTexture("assets/textures/shrek_smith.jpg", GL_RGB);

	// Attribute binding
	vao.AddAttibute(0, 3, GL_FALSE, 8, 0);
	vao.AddAttibute(1, 3, GL_FALSE, 8, 3);
	vao.AddAttibute(2, 3, GL_FALSE, 8, 6);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GLCall(glClearColor(0.2f, 0.2f, 0.23f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		projection = glm::perspective(glm::radians(45.0f), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);;
		view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		
		// Draw the triangle
		shader.Bind();
		shader.setUniformMat4f("projection", projection);
		shader.setUniformMat4f("view", view);
		shader.setUniformMat4f("model", model);

		vao.Bind();
		ebo.Bind();
		for (unsigned int i = 0; i < nCubes; i++) {

			updateModel(glm::translate(glm::mat4(1.0f), cubePositions[i]));
			shader.setUniformMat4f("model", model);
			GLCall(glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0));
		}

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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		xAngle = xAngle == 360.0f ? xAngle = 0.0f * deltaTime : xAngle += 120.0f * deltaTime;
		updateModel();
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		xAngle = xAngle == 0.0f ? xAngle = 360.0f * deltaTime : xAngle -= 120.0f * deltaTime;
		updateModel();
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		yAngle = yAngle == 360.0f ? yAngle = 0.0f * deltaTime : yAngle += 120.0f * deltaTime;
		updateModel();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		yAngle = yAngle == 0.0f ? yAngle = 360.0f * deltaTime : yAngle -= 120.0f * deltaTime;
		updateModel();
	}
	
	/*if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		cameraPosition.z = -0.03f;
		updateView();
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		cameraPosition.z = 0.03f;
		updateView();
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		cameraPosition.x = -0.03f;
		updateView();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		cameraPosition.x = 0.03f;
		updateView();
	}*/
	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


}

void updateView() {
	view = glm::translate(view, cameraPosition);
	cameraDirection = glm::normalize(cameraPosition - cameraTarget);
}

void updateModel(glm::mat4 traslation) {
	glm::mat4 xRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 yRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(yAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));
	model = traslation * xRotationMatrix * yRotationMatrix * scaleMatrix;
}

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	SRC_WIDTH = newWidth;
	SRC_HEIGHT = newHeight;
	/*std::cout << "resolution: " << width << "x" << height << std::endl;*/
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	float newScale = scaleFactor + 0.05f * yoffset;
	if (newScale <= 2 && newScale >= 0) {
		scaleFactor = newScale;
	}
	updateModel();
	std::cout << "scale Factor: " << scaleFactor << ", new scale: " << newScale << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
		if (nCubes < 10) {
			nCubes++;
		}
	}
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
		if (nCubes > 0) {
			nCubes--;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);


}



