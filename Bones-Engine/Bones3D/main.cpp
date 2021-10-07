#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//abstractions
#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Mesh.h"


// note: // I FUCKING HATE LINKERS

//Mesh loadObj(const std::string& filepath)
//{
	
//}


std::vector<Vertex> fat(float pset[], unsigned int size) 
{

	std::vector<Vertex> verts;
	for (unsigned int i = 0; i < size/3; i++) {
		Vertex v = { pset[3*i], pset[3 * i + 1], pset[3 * i + 2], 1.0f,1.0f,1.0f,1.0f};
		verts.push_back(v);
	}
	std::cout << std::endl;
	return verts;
	
}

int main(void)
{	
	
	int width = 640;
	int height = 640;
	std::cout << "HELLO MALKHUT" << std::endl;
	std::cout << __cplusplus << std::endl;
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Bones", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
		std::cout << "FUCK!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	float positions[12] = {
		-0.5f, -0.5f, 1.0f, 
		 0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f, 1.0f, 
		-0.5f,  0.5f, 1.0f

	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	float pos2[12] = {
		-0.3f, -0.3f, 0.0f,
		 0.6f, -0.3f, 0.0f,
		 0.6f,  0.6f, -1.0f,
		 -0.3f,  0.6f, 0.0f
	};
	unsigned int ind2[6] = {
		0,1,2,
		2,3,0
	};
	
	/* MANUAL
	VertexArray vao; //automatically binds in VertexArray.cpp during initialization.
	VertexBuffer vbo(positions, sizeof(positions));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); //index, variables per vertex, type, normalize, byteStride, pointer
	IndexBuffer ibo(indices, sizeof(indices));
	
	vao.Unbind();
	ibo.Unbind();
	vbo.Unbind();
	*/
	std::vector<unsigned int> uiv(indices, indices + sizeof(indices) / sizeof(indices[0]));
	std::vector<unsigned int> uiv2(ind2, ind2 + sizeof(ind2) / sizeof(ind2[0]));
	Mesh mesh(fat(positions, sizeof(positions) / sizeof(float)), uiv);
	Mesh other(fat(pos2, sizeof(pos2) / sizeof(float)), uiv2);
	std::vector<Mesh*> meshes;
	meshes.push_back(&mesh);
	meshes.push_back(&other);

	Shader simple("simple.shader"); //Shaders will exist seperately from Meshes, particularly for the ease of assigning uniforms and attributes.
	Shader simpler("uniform.shader");
	
	mesh.setShader(simple.getID());
	other.setShader(simpler.getID());
	
	simple.setUniform4f("uColor", 0.1f, 0.3f, 0.5f, 1.0f);
	simple.Unbind();
	simpler.Unbind();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		double modifier = 1.0f;
		float timecolor = (float)modf((float)(glfwGetTime()),&modifier);
		simpler.setUniform1f("uTime", (float)(glfwGetTime())); 
		/*
		NOTITIA:
		setUniform(n)f must be called while the shader is bound for some fuckin' reason.
		One way to implement this into the Mesh system would be to add a map-list that correlates uniform/varying names with their values.
		*/
		for (Mesh* activemesh : meshes) {
			activemesh->draw();
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
