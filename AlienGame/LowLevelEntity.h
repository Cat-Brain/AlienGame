#include "Entity.h"

class RenderEntity : public Entity
{
public:
	Shader* shader;
	Mesh* mesh;

	RenderEntity(Shader* shader, Mesh* mesh, vec3 pos = vec3(0.0f), vec3 rot = vec3(0.0f), vec3 scale = vec3(1.0f)) :
		Entity(pos, rot, scale), shader(shader), mesh(mesh)
	{ }

	void DUpdate(Window* window, float deltaTime) override
	{
		shader->Use();
		glm::mat4 transform = glm::translate(glm::mat4(1), pos);
		transform *= glm::mat4(glm::quat(rot));
		transform = glm::scale(transform, scale);
		shader->SetMat4(transform, "transform");
		shader->SetMat4(window->view, "view");
		shader->SetMat4(window->perspective, "perspective");
		shader->SetVec3(window->playerPos, "playerPos");
		mesh->Update();
	}
};