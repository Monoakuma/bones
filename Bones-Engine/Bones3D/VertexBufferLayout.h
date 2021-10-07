#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferDefinition
{
	unsigned int type;
	unsigned int count;
	bool normalized;
};

class VertexBufferLayout 
{
private:
	std::vector<VertexBufferDefinition> vElements;
	unsigned int bStride;
public:
	VertexBufferLayout()
		: bStride(0) {}
	/*
	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count, bool normalized)
	{
		vElements.push_back({GL_FLOAT,count,normalized});
		bStride += sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(int count, bool normalized)
	{
		vElements.push_back({ GL_UNSIGNED_INT,count,normalized });
		bStride += sizeof(GLunit);
	}

	template<>
	void Push<unsigned char>(int count, bool normalized)
	{
		vElements.push_back({ GL_UNSIGNED_BYTE, count , normalized });
		bStride += sizeof(GLbyte);
	}
	*/
	inline const std::vector<VertexBufferDefinition> GetElements() const { return vElements; }

	inline unsigned int getStride() const { return bStride; }
};