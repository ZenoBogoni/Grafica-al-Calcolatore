#pragma once
class VertexArray
{
private:
	unsigned int m_ID;
	unsigned int m_Stride;
public:
	VertexArray();
	~VertexArray();

	void AddAttibute(unsigned int position, int size, bool normalized, int  stride, unsigned int  offset);
	void Bind() const;
	void Unbind() const;
	void Enable(unsigned int position) const;
	void Disable(unsigned int position) const;

	inline unsigned int getStride() const { return m_Stride; }
};

