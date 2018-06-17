#include "RenderComponent.h"
#include <stddef.h>

#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GameSetup.h"

void RenderComponent::Render(CameraComponent* camera)
{
	modelinfo->model.shader->UseShader();
	//modelinfo->bindTextures();

	//update? or render? Render: because interpolation should be applied
	model = glm::mat4();

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

	parent->transform.modelMatrix = model;

	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(camera->view * model)));
	modelinfo->model.shader->SetVec3("camPos", camera->parent->transform.position);

	//setting matrices / must be set while using the shader program or it won't work
	glUniformMatrix4fv(modelinfo->model.shader->shaderlocations.modelmatrixloc, 1, GL_FALSE, glm::value_ptr(model)); //model
	glUniformMatrix4fv(modelinfo->model.shader->shaderlocations.viewmatrixloc, 1, GL_FALSE, glm::value_ptr(camera->view)); //view
	glUniformMatrix4fv(modelinfo->model.shader->shaderlocations.projectionmatrixloc, 1, GL_FALSE, glm::value_ptr(camera->projection)); //projection
	glUniformMatrix3fv(modelinfo->model.shader->shaderlocations.normalmatrixloc, 1, GL_FALSE, glm::value_ptr(normalMatrix)); //normalmatrix

	//glBindVertexArray(modelinfo->VAO);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	modelinfo->model.Draw(modelinfo->model.shader);

	glUseProgram(0);

}

void RenderComponent::init(uint32_t id)
{
	Component::init(id);

	Debug("Renderinit" << std::endl);
	modelinfo = parent->GetComponent<ModelComponent>();

	parent->GetSetup()->AddDrawable(this);

	if (modelinfo == nullptr)
	{
		hasmodelinfo = true;
		Debug("No model component found" << std::endl);
		//inactive state
	}
}

void RenderComponent::freeData()
{
	parent->GetSetup()->GetObjectContainer()->drawables.erase(GetID());
}

RenderComponent::RenderComponent()
{
}


RenderComponent::~RenderComponent()
{
}