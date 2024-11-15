#include <iostream>
class Texture
{
private: 
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& path, unsigned int type);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void setMinFilter(int filter) const;
	void setMagFilter(int filter) const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
};

