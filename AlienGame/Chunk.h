#include "LowLevelEntity.h"

class Chunk : public RenderEntity
{
public:
	Texture data;

	Chunk(unsigned char* data, Shader* shader, Mesh* mesh, vec3 pos = glm::vec3(0), vec3 rot = vec3(0.0f), float scale = 1.0f) :
		RenderEntity(shader, mesh, pos, rot, glm::vec3(scale)), data(data, 16, 16, 16)
	{ }

	void DUpdate(Window* window, float deltaTime) override
	{
		data.Bind(GL_TEXTURE_3D);
		shader->Use();
		glm::mat4 transform = glm::translate(glm::mat4(1), pos);
		transform *= glm::mat4(glm::quat(rot));
		transform = glm::scale(transform, scale);
		shader->SetMat4(transform, "transform");
		shader->SetMat4(window->view, "view");
		shader->SetMat4(window->perspective, "perspective");
		shader->SetVec3(window->playerPos, "playerPos");
		shader->SetVec3(pos, "pos");
		shader->SetFloat(scale.x, "scale");
		shader->SetTex3D(data, "voxels");
		mesh->Update();
	}
};