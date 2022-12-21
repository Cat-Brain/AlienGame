#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using glm::vec2;
using glm::vec3;
using glm::ivec2;
using glm::ivec3;

typedef unsigned int uint;

float tTime = 0.0f;

char* OpenFile(const char* where)
{
	std::ifstream file(where, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		std::cout << "Unable to open file!\n";
		return nullptr;
	}
	uint size = file.tellg();
	char* result = new char[size + 1];
	file.seekg(0, std::ios::beg);
	file.read(result, size);
	file.close();
	result[size] = '\0';
	return result;
}

struct Key
{
	bool pressed, held, released;

	Key(bool pressed = false, bool held = false, bool released = false) :
		pressed(pressed), held(held), released(released)
	{ }
};

struct Inputs
{
	Key w, a, s, d,
		f;
	vec2 mousePos, mouseDelta;

	Inputs() = default;

	void Update(GLFWwindow* window)
	{
		bool nowPressed;

		nowPressed = glfwGetKey(window, GLFW_KEY_W);
		w.pressed = nowPressed & !w.held;
		w.released = !nowPressed & w.held;
		w.held = nowPressed;

		nowPressed = glfwGetKey(window, GLFW_KEY_A);
		a.pressed = nowPressed & !a.held;
		a.released = !nowPressed & a.held;
		a.held = nowPressed;

		nowPressed = glfwGetKey(window, GLFW_KEY_S);
		s.pressed = nowPressed & !s.held;
		s.released = !nowPressed & s.held;
		s.held = nowPressed;

		nowPressed = glfwGetKey(window, GLFW_KEY_D);
		d.pressed = nowPressed & !d.held;
		d.released = !nowPressed & d.held;
		d.held = nowPressed;


		nowPressed = glfwGetKey(window, GLFW_KEY_F);
		f.pressed = nowPressed & !f.held;
		f.released = !nowPressed & f.held;
		f.held = nowPressed;
	}
};