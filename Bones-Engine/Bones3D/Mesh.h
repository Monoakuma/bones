#pragma once
#include "Shader.h"
#include "renderer.h"
#include <iostream>
#include <string>
#include <vector>

struct Vertex {
	// position
	float x,y,z;
	// color
	float r,g,b,a;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;

		prepareMesh();
	}
	~Mesh() 
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		disable();
	}
	void setShader(unsigned int shaderID) 
	{
		shader = shaderID;
		glUseProgram(shader);
	}
	void draw() //A crash in a draw call is in 99.99999% of the cases an enabled generic vertex attribute (via glEnableVertexAttribArray) which has no buffer source (via glVertexAttribPointer).
	{
		//std::cout << "MESH DRAW:" << &vao << std::endl;
		TestCall(glBindVertexArray(vao)); 
		TestCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		TestCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); 
		TestCall(glUseProgram(shader));
		TestCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0)); 
		disable();

	}
	void disable() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

private:
	unsigned int vao, vbo, ibo, shader;
	void prepareMesh()
	{
		//VAO,VBO,IBO//
		TestCall(glGenVertexArrays(1, &vao));
		TestCall(glBindVertexArray(vao));

		TestCall(glGenBuffers(1, &vbo));
		TestCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

		TestCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));
		TestCall(glEnableVertexAttribArray(0));
		TestCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0)); //index, variables per vertex, type, normalize, byteStride, pointer
		TestCall(glGenBuffers(1, &ibo));
		TestCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
		TestCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
		TestCall(glBindVertexArray(0));
		std::cout << "MESH:" << "MESH ENABLED" << std::endl;
	}
};