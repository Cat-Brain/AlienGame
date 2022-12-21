#include "Chunk.h"

class Player : public Entity
{
public:
	float moveSpeed, sensitivity;

	Player(float moveSpeed, float sensitivity, vec3 pos = vec3(0), vec3 rot = vec3(0.0f, -90.0f, 0.0f), vec3 scale = vec3(1)):
		Entity(pos, rot, scale), moveSpeed(moveSpeed), sensitivity(sensitivity)
	{ }

	void Update(Window* window, float deltaTime) override
	{
		rot.y += inputs.mouseDelta.x * sensitivity;
		rot.x += inputs.mouseDelta.y * sensitivity;
		if (rot.x > 89.0f)
			rot.x = 89.0f;
		if (rot.x < -89.0f)
			rot.x = -89.0f;
		vec3 forward, right, up;
		float cosOfPitch = cos(glm::radians(rot.x));
		forward.x = cos(glm::radians(rot.y)) * cosOfPitch; // Note that we convert the angle to radians first
		forward.y = sin(glm::radians(rot.x));
		forward.z = sin(glm::radians(rot.y)) * cosOfPitch;
		right = glm::normalize(glm::cross(forward, { 0.0f, 1.0f, 0.0f }));
		up = glm::normalize(glm::cross(right, forward));

		if (glfwGetKey(window->window, GLFW_KEY_W))
			pos += forward * (moveSpeed * deltaTime);
		if (glfwGetKey(window->window, GLFW_KEY_A))
			pos -= right * (moveSpeed * deltaTime);
		if (glfwGetKey(window->window, GLFW_KEY_S))
			pos -= forward * (moveSpeed * deltaTime);
		if (glfwGetKey(window->window, GLFW_KEY_D))
			pos += right * (moveSpeed * deltaTime);
		if (glfwGetKey(window->window, GLFW_KEY_E))
			pos += up * (moveSpeed * deltaTime);
		if (glfwGetKey(window->window, GLFW_KEY_Q))
			pos -= up * (moveSpeed * deltaTime);

		window->playerPos = pos;
		window->view = glm::lookAt(pos, pos + forward, { 0.0f, 1.0f, 0.0f });
	}
};