#include "LineRenderer.h"
#include "CollisionComponent.h"

void LineRenderer::Draw(CameraComponent* cam)
{
	CollisionComponent::lineshader->UseShader();

	//transformation
	glm::mat4 model;

	model = glm::translate(model, transform.position);

	model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));

	model = glm::scale(model, transform.scale);

	//mvp matrix
	glm::mat4 modelviewprojection = cam->projection * cam->view * model;

	//get uniform locations
	GLuint mvploc = glGetUniformLocation(CollisionComponent::lineshader->shaderid_, "mvpMat");

	//set uniforms, matrix and color
	glUniformMatrix4fv(mvploc, 1, GL_FALSE, glm::value_ptr(modelviewprojection));
	CollisionComponent::lineshader->SetVec3("color", color);

	//draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, vertices.size());

	glUseProgram(0);
}

LineRenderer::LineRenderer(Bounds bounds, CollisionComponent* coll)
{
	parent = coll;
	glm::vec3 cube[]{
		//lower square
		glm::vec3(bounds.minBounds.x, bounds.minBounds.y, bounds.minBounds.z),
		glm::vec3(bounds.maxBounds.x, bounds.minBounds.y, bounds.minBounds.z),

		glm::vec3(bounds.maxBounds.x, bounds.minBounds.y, bounds.minBounds.z),
		glm::vec3(bounds.maxBounds.x, bounds.minBounds.y, bounds.maxBounds.z),

		glm::vec3(bounds.maxBounds.x, bounds.minBounds.y, bounds.maxBounds.z),
		glm::vec3(bounds.minBounds.x, bounds.minBounds.y, bounds.maxBounds.z),

		glm::vec3(bounds.minBounds.x, bounds.minBounds.y, bounds.maxBounds.z),
		glm::vec3(bounds.minBounds.x, bounds.minBounds.y, bounds.minBounds.z),

		//upper square
		glm::vec3(bounds.minBounds.x, bounds.maxBounds.y, bounds.minBounds.z),
		glm::vec3(bounds.maxBounds.x, bounds.maxBounds.y, bounds.minBounds.z),

		glm::vec3(bounds.maxBounds.x, bounds.maxBounds.y, bounds.minBounds.z),
		glm::vec3(bounds.maxBounds.x, bounds.maxBounds.y, bounds.maxBounds.z),

		glm::vec3(bounds.maxBounds.x, bounds.maxBounds.y, bounds.maxBounds.z),
		glm::vec3(bounds.minBounds.x, bounds.maxBounds.y, bounds.maxBounds.z),

		glm::vec3(bounds.minBounds.x, bounds.maxBounds.y, bounds.maxBounds.z),
		glm::vec3(bounds.minBounds.x, bounds.maxBounds.y, bounds.minBounds.z),

		//corner lines
		glm::vec3(bounds.minBounds.x, bounds.minBounds.y, bounds.minBounds.z),
		glm::vec3(bounds.minBounds.x, bounds.maxBounds.y, bounds.minBounds.z),

		glm::vec3(bounds.maxBounds.x, bounds.minBounds.y, bounds.minBounds.z),
		glm::vec3(bounds.maxBounds.x, bounds.maxBounds.y, bounds.minBounds.z),

		glm::vec3(bounds.maxBounds.x, bounds.minBounds.y, bounds.maxBounds.z),
		glm::vec3(bounds.maxBounds.x, bounds.maxBounds.y, bounds.maxBounds.z),

		glm::vec3(bounds.minBounds.x, bounds.minBounds.y, bounds.maxBounds.z),
		glm::vec3(bounds.minBounds.x, bounds.maxBounds.y, bounds.maxBounds.z)
	};

	vertices = std::vector<glm::vec3>(cube, cube + sizeof(cube) / sizeof(glm::vec3));
	createBuffers(cube);

}

LineRenderer::LineRenderer(CollisionComponent* coll)
{
	parent = coll;
	glm::vec3 cube[]{

		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),

		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),

		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),

		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f)
	};

	vertices = std::vector<glm::vec3>(cube, cube + sizeof(cube) / sizeof(glm::vec3));
	createBuffers(cube);
}


LineRenderer::~LineRenderer()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}


void LineRenderer::createBuffers(glm::vec3 * array)
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0); //position
	glEnableVertexAttribArray(0); //Enabling the attribute because they are disabled by default
}
