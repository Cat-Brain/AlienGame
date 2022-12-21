#include "Window.h"

class Entity
{
public:
	vec3 pos, rot, scale;

	Entity(vec3 pos = vec3(0.0f), vec3 rot = vec3(0.0f), vec3 scale = vec3(1.0f)) :
		pos(pos), rot(rot), scale(scale)
	{ }

	virtual void Update(Window* window, float deltaTime) { }

	virtual void DUpdate(Window* window, float deltaTime) { }
};