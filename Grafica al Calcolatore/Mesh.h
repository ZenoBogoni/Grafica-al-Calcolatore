#ifndef MESH_HH
#define MESH_HH

#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<Texture> textures);

	void Draw(Shader &shader);

private:
	unsigned int VBO, VAO, EBO;

	void setupMesh();

};

#endif


