#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
#include "Renderer.h"
#include <glad/glad.h>


Texture::Texture(const std::string& path)
	:ID(0), m_FilePath(path), m_Width(0), m_Height(0),m_BPP(0)
{
	GLCall(glGenTextures(1, &ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));

	stbi_set_flip_vertically_on_load(true);
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);
	if (m_LocalBuffer) {
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(m_LocalBuffer);

}

Texture::~Texture()
{
}

void Texture::Bind(unsigned int slot) const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
