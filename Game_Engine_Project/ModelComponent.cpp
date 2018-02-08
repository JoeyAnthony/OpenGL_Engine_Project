#include "ModelComponent.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

void ModelComponent::init(uint32_t id)
{
	Component::init(id);

	static const Vertex cubeVertices[] = {
		Vertex(glm::vec3(-1.0, -1.0, 1.0),		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),		glm::vec2(0.0f, 0.0f)),		// bottom left back		0
		Vertex(glm::vec3(1.0, -1.0, 1.0),		glm::vec4(1.0f, 0.0f, 0.0f,	1.0f),		glm::vec2(1.0f, 0.0f)),		// bottom right back	1
		Vertex(glm::vec3(-1.0, 1.0, 1.0),		glm::vec4(1.0f, 1.0f, 0.0f,	1.0f),		glm::vec2(0.0f, 1.0f)),		//top left back			2
		Vertex(glm::vec3(1.0,  1.0, 1.0),		glm::vec4(0.0f, 0.0f, 1.0f,	1.0f),		glm::vec2(1.0f, 1.0f)),		// top right back		3

		Vertex(glm::vec3(-1.0, -1.0, -1.0),		glm::vec4(0.0f, 1.0f, 0.0f,	1.0f),		glm::vec2(0.0f, 0.0f)),		// bottom left front	4
		Vertex(glm::vec3(1.0, -1.0, -1.0),		glm::vec4(1.0f, 0.0f, 0.0f,	1.0f),		glm::vec2(1.0f, 0.0f)),		// bottom right front	5
		Vertex(glm::vec3(-1.0,  1.0, -1.0),		glm::vec4(1.0f, 1.0f, 0.0f,	1.0f),		glm::vec2(0.0f, 1.0f)),		//top left front		6
		Vertex(glm::vec3(1.0,  1.0, -1.0),		glm::vec4(0.0f, 0.0f, 1.0f,	1.0f),		glm::vec2(1.0f, 1.0f))		// top right front		7
	};

	static const unsigned int cubeIndices[] = {
		//front
		4, 5, 7,
		7, 6, 4,
		//rightside
		5, 1, 3,
		3, 7, 5,
		//back
		1, 0, 2,
		2, 3, 1,
		//left
		0, 4, 6,
		6, 2, 0,
		//bottom
		4, 5, 1,
		1, 0, 4,
		//top
		6, 7, 3,
		3, 2, 6
	};


	//create vbo and vao
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	//bind vao
	glBindVertexArray(VAO);

	//bind vbo buffer and store vertex data in it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	//bind and buffer vbo array, the vao will hold it too
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	//set vertex attributes for shaders
	/*
	(location = 0) vertex position location is 0 like in the shader
	Since the previously defined VBO was bound before calling glVertexAttribPointer,
	vertex attribute 0 is now associated with its vertex data
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Enabling the attribute because they are disabled by default
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);


	////texture
	//Texture texture = Texture("Assets/Textures/lena.png");
	//Texture texture2 = Texture("Assets/Textures/godzilla.jpg");
	//glActiveTexture(GL_TEXTURE0);
	//texture.Bind();
	//glActiveTexture(GL_TEXTURE1);
	//texture2.Bind();
	
	//shader
	transformshader = Shader("DefaultShader.vs", "DefaultShader.fs");
	transformshader.UseShader(); //bind shader

	////set texture samples in shader AFTER useshader
	//transformshader.SetInt("texture1", 0);
	//transformshader.SetInt("texture2", 1);

	////textures
	//addTexture("texture1", "Assets/Textures/Sanic2.png");
	//addTexture("texture2", "Assets/Textures/thomas420.jpg");
	

	glUseProgram(0); //unbind shader
}

void ModelComponent::addShader(std::string vs, std::string fs)
{
	transformshader = Shader(vs.c_str(), fs.c_str());
}

void ModelComponent::addTexture(std::string uniformName ,std::string path)
{
	//texture
	Texture texture = Texture(path);
	texture.texSampler = GL_TEXTURE0 + texcount;
	texture.texSamplerID = texcount;

	//Texture texture2 = Texture("Assets/Textures/godzilla.jpg");
	glActiveTexture(texture.texSampler);
	texture.Bind();
	//glActiveTexture(GL_TEXTURE1);
	//texture2.Bind();

	transformshader.UseShader(); //bind shader

	//set texture samples in shader AFTER useshader
	transformshader.SetInt(uniformName, texture.texSamplerID);

	texture.Unbind();
	textures.push_back(texture);
	texcount++;
}

void ModelComponent::bindTextures()
{
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(textures[i].texSampler);
		textures[i].Bind();
	}
}




ModelComponent::ModelComponent()
{

}

ModelComponent::~ModelComponent(void)
{
	//glDeleteBuffers();
}






