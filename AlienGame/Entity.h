#include "Window.h"

class Entity
{
public:
	Shader* shader;
	Mesh* mesh;

	Entity(Shader* shader, Mesh* mesh) :
		shader(shader), mesh(mesh)
	{ }

	void Update(Window* window)
	{
		shader->Use();
		mesh->Update();
	}
};