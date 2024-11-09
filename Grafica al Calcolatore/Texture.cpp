#include "Texture.h"
#include "Renderer.h"

Texture::Texture(const std::string& path)
	:ID(0), m_FilePath(path), m_Width(0), m_Height(0),m_BPP(0)
{
}

Texture::~Texture()
{
}

void Texture::Bind(unsigned int slot) const
{
}

void Texture::Unbind() const
{
}
