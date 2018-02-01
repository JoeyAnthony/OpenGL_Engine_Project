#include "RenderComponent.h"
#include <stddef.h>

#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GameSetup.h"

void RenderComponent::Render(CameraComponent* camera)
{
	modelinfo->transformshader.UseShader();

	//update? or render? Render: because interpolation should be applied
	glm::mat4 model;

	//first scale, then rotate last translate. read from right to left so it is:
	//translate, rotate, scale. most right matrix is multiplied first with the vector

	//translate
	model = glm::translate(model, parent->transform.position);

	//rotation
	model = glm::rotate(model, glm::radians(parent->transform.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(parent->transform.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(parent->transform.rotation.z), glm::vec3(0, 0, 1));

	//scaling
	model = glm::scale(model, parent->transform.scale);

	//setting matrices / must be set while using the shader program or it won't work
	glUniformMatrix4fv(modelinfo->shaderlocations.modelmatrixloc, 1, GL_FALSE, glm::value_ptr(model)); //model
	glUniformMatrix4fv(modelinfo->shaderlocations.viewmatrixloc, 1, GL_FALSE, glm::value_ptr(camera->view)); //view
	glUniformMatrix4fv(modelinfo->shaderlocations.projectionmatrixloc, 1, GL_FALSE, glm::value_ptr(camera->projection)); //projection

	glBindVertexArray(modelinfo->VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glUseProgram(0);

}

void RenderComponent::init(uint32_t id)
{
	Component::init(id);

	std::cout << "Renderinit" << std::endl;
	modelinfo = parent->GetComponent<ModelComponent>();

	parent->GetSetup()->AddDrawable(this);

	if (modelinfo == nullptr)
	{
		hasmodelinfo = true;
		std::cout << "No model component found" << std::endl;
		//inactive state
	}
}

RenderComponent::RenderComponent()
{
}


RenderComponent::~RenderComponent()
{
}